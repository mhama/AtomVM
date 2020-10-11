
#ifndef _M5STACK_DRIVER_H_
#define _M5STACK_DRIVER_H_

#include "context.h"
#include "term.h"
#include "m5stack_bridge.h"

void m5_driver_init(GlobalContext *glb);
void m5_port_init(Context *ctx, term opts);

#endif

