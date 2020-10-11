/***************************************************************************
 *   Copyright 2017 by Davide Bettio <davide@uninstall.it>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "freertos/FreeRTOS.h"
#include "esp_partition.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

#include "atom.h"
#include "avmpack.h"
#include "bif.h"
#include "context.h"
#include "globalcontext.h"
#include "iff.h"
#include "module.h"
#include "socket_driver.h"
#include "utils.h"
#include "term.h"

#include "esp32_sys.h"
#include "nvs_flash.h"

#include "m5stack_driver.h"

const void *avm_partition(const char *partition_name, int *size);

void app_main()
{
    nvs_flash_init();
    tcpip_adapter_init();

    esp32_sys_queue_init();

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        fprintf(stderr, "Warning: Erasing flash...\n");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    int size;
    const void *main_avm = avm_partition("main.avm", &size);

    uint32_t startup_beam_size;
    const void *startup_beam;
    const char *startup_module_name;

    printf("Booting file mapped at: %p, size: %i\n", main_avm, size);

    GlobalContext *glb = globalcontext_new();

    socket_driver_init(glb);

    // m5 specific
    m5_driver_init(glb);
    M5Stack_ShowMessageAndWait("Hello from AtomVM (m5_driver)!");

    if (!avmpack_is_valid(main_avm, size) || !avmpack_find_section_by_flag(main_avm, BEAM_START_FLAG, &startup_beam, &startup_beam_size, &startup_module_name))
    {
        fprintf(stderr, "error: invalid AVM Pack\n");
        abort();
    }
    struct AVMPackData *avmpack_data = malloc(sizeof(struct AVMPackData));
    if (IS_NULL_PTR(avmpack_data)) {
        fprintf(stderr, "Memory error: Cannot allocate AVMPackData.\n");
        abort();
    }
    avmpack_data->data = main_avm;
    list_append(&glb->avmpack_data, (struct ListHead *) avmpack_data);
    glb->avmpack_platform_data = NULL;

    const void *lib_avm = avm_partition("lib.avm", &size);
    if (!IS_NULL_PTR(lib_avm) && avmpack_is_valid(lib_avm, size)) {
        avmpack_data = malloc(sizeof(struct AVMPackData));
        if (IS_NULL_PTR(avmpack_data)) {
            fprintf(stderr, "Memory error: Cannot allocate AVMPackData.\n");
            abort();
        }
        avmpack_data->data = lib_avm;
        list_append(&glb->avmpack_data, (struct ListHead *) avmpack_data);
    } else {
        fprintf(stderr, "Unable to mount lib.avm partition.  Ignoring...\n");
    }

    Module *mod = module_new_from_iff_binary(glb, startup_beam, startup_beam_size);
    if (IS_NULL_PTR(mod)) {
        fprintf(stderr, "Error.  Unable to load startup module %s\n", startup_module_name);
        abort();
    }
    globalcontext_insert_module_with_filename(glb, mod, startup_module_name);
    Context *ctx = context_new(glb);
    ctx->leader = 1;

    printf("Starting: %s...\n", startup_module_name);
    printf("---\n");
    context_execute_loop(ctx, mod, "start", 0);
    term ret_value = ctx->x[0];
    fprintf(stderr, "AtomVM finished with return value = ");
    term_display(stderr, ret_value, ctx);
    fprintf(stderr, "\n");

    fprintf(stderr, "going to sleep forever..\n");
    while(1) {
        // avoid task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time
        // ..
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

const void *avm_partition(const char *partition_name, int *size)
{
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, partition_name);
    if (!partition) {
        printf("AVM partition not found.\n");
        *size = 0;
        return NULL;

    } else {
        printf("Found AVM partition: size: %i, address: 0x%x\n", partition->size, partition->address);
        *size = partition->size;
    }

    const void *mapped_memory;
    spi_flash_mmap_handle_t unmap_handle;
    if (esp_partition_mmap(partition, 0, partition->size, SPI_FLASH_MMAP_DATA, &mapped_memory, &unmap_handle) != ESP_OK) {
        printf("Failed to map BEAM partition\n");
        abort();
        return NULL;
    }

    UNUSED(unmap_handle);

    return mapped_memory;
}
