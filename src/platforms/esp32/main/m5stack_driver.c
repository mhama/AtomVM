#include "m5stack_bridge.h"
#include "m5stack_driver.h"

#include "atom.h"
#include "defaultatoms.h"
#include "platform_defaultatoms.h"
#include "globalcontext.h"
#include "interop.h"
#include "mailbox.h"
#include "term.h"
#include "trace.h"

static void m5stack_consume_mailbox(Context *ctx);


void m5_driver_init(GlobalContext *glb)
{
    M5Stack_Init();
}

void m5_port_init(Context *ctx, term opts)
{
    GlobalContext *glb = ctx->global;
    struct ESP32PlatformData *platform = glb->platform_data;
    ctx->native_handler = m5stack_consume_mailbox;
}

static term m5_show_message(Context *ctx, term req)
{
    term msg_term = term_get_tuple_element(req, 1);
    int ok;
    char *msg = interop_term_to_string(msg_term, &ok);
    if (!msg || !ok) {
        TRACE("m5driver m5_show_message error.");
        return ERROR_ATOM;
    }
    M5Stack_ShowMessage(msg);
    free(msg);
    return OK_ATOM;
}

static term m5_button_read(Context *ctx, term req)
{
    term button_term = term_get_tuple_element(req, 1);
    if (!term_is_integer(button_term)) {
        TRACE("m5: m5_button_read: unrecognized button index.");
        printf("m5: m5_button_read: unrecognized button index.\n");
        return ERROR_ATOM;
    }
    avm_int_t button_index = term_to_int(button_term);
    int res = M5Stack_ButtonRead(button_index);
    printf("m5: m5_button_read: res:%d\n", res);
    return res ? TRUE_ATOM : FALSE_ATOM;
}

static void m5stack_consume_mailbox(Context *ctx)
{
    Message *message = mailbox_dequeue(ctx);
    term msg = message->message;

    term pid = term_get_tuple_element(msg, 0);
    term ref = term_get_tuple_element(msg, 1);
    term req = term_get_tuple_element(msg, 2);

    term cmd = term_is_atom(req) ? req : term_get_tuple_element(req, 0);

    int local_process_id = term_to_local_process_id(pid);
    Context *target = globalcontext_get_process(ctx->global, local_process_id);

    term ret;

    switch (cmd) {
        case M5_SHOW_MESSAGE_ATOM:
            ret = m5_show_message(ctx, req);
            break;

        case M5_BUTTON_READ_ATOM:
            ret = m5_button_read(ctx, req);
            break;

        default:
            TRACE("m5: error: unrecognized command: %lx\n", cmd);
            ret = ERROR_ATOM;
    }

    printf("m5: m5stack_consume_mailbox ending\n");

    free(message);

    UNUSED(ref);

    printf("m5: m5stack_consume_mailbox before mailbox_send()\n");

    mailbox_send(target, ret);
}
