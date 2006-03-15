#include <stdio.h>
#include <stdint.h>

typedef uint64_t __u64;
typedef __u64 ipl_t;
typedef __u64 __address;

#define __amd64_TYPES_H__
#include "../../arch/amd64/include/context.h"

#define FILENAME "../../arch/amd64/include/context_offset.h"

int main(void)
{
	FILE *f;
	struct context ctx;
	struct context *pctx = &ctx;

	struct interrupt_context ictx;
	struct interrupt_context *ipctx = &ictx;

	f = fopen(FILENAME,"w");
	if (!f) {
		perror(FILENAME);
		return 1;
	}

	fprintf(f, "/* This file is automatically generated by %s. */\n", __FILE__);	

	fprintf(f,"#define OFFSET_SP  0x%x\n", ((int) &pctx->sp) - (int) pctx);
	fprintf(f,"#define OFFSET_PC  0x%x\n", ((int) &pctx->pc) - (int) pctx);
	fprintf(f,"#define OFFSET_RBX 0x%x\n", ((int) &pctx->rbx) - (int) pctx);
	fprintf(f,"#define OFFSET_RBP 0x%x\n", ((int) &pctx->rbp) - (int) pctx);
	fprintf(f,"#define OFFSET_R12 0x%x\n", ((int) &pctx->r12) - (int) pctx);
	fprintf(f,"#define OFFSET_R13 0x%x\n", ((int) &pctx->r13) - (int) pctx);
	fprintf(f,"#define OFFSET_R14 0x%x\n", ((int) &pctx->r14) - (int) pctx);
	fprintf(f,"#define OFFSET_R15 0x%x\n", ((int) &pctx->r15) - (int) pctx);
	fprintf(f,"#define OFFSET_IPL 0x%x\n", ((int) &pctx->ipl) - (int) pctx);

	fclose(f);

	return 0;
}
