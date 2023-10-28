#include <err.h>
#include <stdio.h>
#include <string.h>

#include <tee_client_api.h>
#include <iot_ta.h>

int main(void)
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = TA_IOT_EXAMPLE_UUID;
	uint32_t err_origin;


	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);


	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);


	memset(&op, 0, sizeof(op));


	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].value.a = 1;


	printf("\n\n========== IoT EXAMPLE ========== \n");
	printf(" 0: Machinery is off \n 1: Machinery is on\n\n");
	printf("The machine current state is %d \n\n", op.params[0].value.a);
	printf("Now Invoking Trusted Application (TA)...\n");

	res = TEEC_InvokeCommand(&sess, TA_IOT_CMD_TURN_OFF, &op, &err_origin);
	if (res != TEEC_SUCCESS)
    errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);
    printf("... TA Invoked! \n\nThe machine current state is now %d\n", op.params[0].value.a);



	TEEC_CloseSession(&sess);
	TEEC_FinalizeContext(&ctx);

	return 0;
}
