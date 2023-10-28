#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <iot_ta.h>


TEE_Result TA_CreateEntryPoint(void)
{
	DMSG("has been called");

	return TEE_SUCCESS;
}


void TA_DestroyEntryPoint(void)
{
	DMSG("has been called");
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types,
		TEE_Param __maybe_unused params[4],
		void __maybe_unused **sess_ctx)
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	DMSG("has been called");

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	(void)&params;
	(void)&sess_ctx;

	IMSG("Hello World! IoT example was called.\n");

	return TEE_SUCCESS;
}



void TA_CloseSessionEntryPoint(void __maybe_unused *sess_ctx)
{
	(void)&sess_ctx; 
	IMSG("Goodbye!\n");
}

static TEE_Result turn_on(uint32_t param_types,
	TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	DMSG("TA has been called to turn on the machine.");

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	IMSG("\n\n\n\nThe machine current state is %u", params[0].value.a);
	params[0].value.a = 1;
	IMSG("Changing state to %u\n\n\n\n", params[0].value.a);

	return TEE_SUCCESS;
}

static TEE_Result turn_off(uint32_t param_types,
	TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	DMSG("TA has been called to turn off the machine.");

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	IMSG("\n\n\n\nThe machine current state is %u", params[0].value.a);
	params[0].value.a = 0;
	IMSG("Changing state to %u\n\n\n\n", params[0].value.a);

	return TEE_SUCCESS;
}



TEE_Result TA_InvokeCommandEntryPoint(void __maybe_unused *sess_ctx,
			uint32_t cmd_id,
			uint32_t param_types, TEE_Param params[4])
{
	(void)&sess_ctx; 

	switch (cmd_id) {
	case TA_IOT_CMD_TURN_ON:
		return turn_on(param_types, params);
	case TA_IOT_CMD_TURN_OFF:
		return turn_off(param_types, params);
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}
