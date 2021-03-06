# whatever flags you want to pass to the C compiler & linker
CL_CFLAGS = -O2

AM_CFLAGS = $(CL_CFLAGS)
AM_CFLAGS += -Wall -std=gnu99
AM_CFLAGS += -I$(top_srcdir)/src/include

AM_LDFLAGS = -lm

lib_LTLIBRARIES = libmusdk.la

nobase_include_HEADERS  = include/mv_std.h
nobase_include_HEADERS += include/env/mv_common.h
nobase_include_HEADERS += include/env/mv_compiler.h
nobase_include_HEADERS += include/env/mv_debug.h
nobase_include_HEADERS += include/env/mv_errno.h
nobase_include_HEADERS += include/env/mv_sys_dma.h
nobase_include_HEADERS += include/env/mv_types.h

libmusdk_la_CFLAGS = $(AM_CFLAGS)
libmusdk_la_LDFLAGS = $(AM_LDFLAGS)

libmusdk_la_SOURCES  = lib/list.c
libmusdk_la_SOURCES += lib/lib_misc.c
libmusdk_la_SOURCES += lib/mem_mng.c
libmusdk_la_SOURCES += lib/uio/uio_find_devices.c
libmusdk_la_SOURCES += lib/uio/uio_find_devices_byname.c
libmusdk_la_SOURCES += lib/uio/uio_free.c
libmusdk_la_SOURCES += lib/uio/uio_get_all_info.c
libmusdk_la_SOURCES += lib/uio/uio_get_device_attributes.c
libmusdk_la_SOURCES += lib/uio/uio_get_event_count.c
libmusdk_la_SOURCES += lib/uio/uio_get_mem_addr.c
libmusdk_la_SOURCES += lib/uio/uio_get_mem_size.c
libmusdk_la_SOURCES += lib/uio/uio_get_mem_name.c
libmusdk_la_SOURCES += lib/uio/uio_get_name.c
libmusdk_la_SOURCES += lib/uio/uio_get_version.c
libmusdk_la_SOURCES += lib/uio/uio_line_from_file.c
libmusdk_la_SOURCES += lib/uio/uio_num_from_filename.c
libmusdk_la_SOURCES += lib/uio/uio_single_mmap.c
libmusdk_la_SOURCES += lib/uio/uio_find_mem_byname.c

libmusdk_la_SOURCES += lib/crypto/mv_md5.c
libmusdk_la_SOURCES += lib/crypto/mv_sha1.c
libmusdk_la_SOURCES += lib/crypto/mv_sha2.c
libmusdk_la_SOURCES += lib/crypto/mv_aes.c

libmusdk_la_SOURCES += env/spinlock.c
libmusdk_la_SOURCES += env/cma.c
libmusdk_la_SOURCES += env/hugepage_mem.c
libmusdk_la_SOURCES += env/sys_dma.c
libmusdk_la_SOURCES += env/of.c
libmusdk_la_SOURCES += env/netdev.c
libmusdk_la_SOURCES += env/sys_iomem.c

nobase_include_HEADERS += include/drivers/mv_net.h
nobase_include_HEADERS += include/drivers/mv_pp2.h
nobase_include_HEADERS += include/drivers/mv_pp2_bpool.h
nobase_include_HEADERS += include/drivers/mv_pp2_cls.h
nobase_include_HEADERS += include/drivers/mv_pp2_hif.h
nobase_include_HEADERS += include/drivers/mv_pp2_ppio.h

libmusdk_la_SOURCES += drivers/ppv2/pp2.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_bm.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_dm.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_port.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_mem.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_gop.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_gop_dbg.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_hw_cls.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_hw_cls_dbg.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_bpool.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_hif.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_ppio.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_cls.c
libmusdk_la_SOURCES += drivers/ppv2/pp2_utils_us.c

libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_cls_common.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_cls_utils.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_cls_db.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_prs.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_flow_rules.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_c3.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_cls_mng.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_flow_rules_debug.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_c3_debug.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_c2.c
libmusdk_la_SOURCES += drivers/ppv2/cls/pp2_c2_debug.c

if SAM_BUILD
# Definitions for SAM driver compilation
nobase_include_HEADERS += include/drivers/mv_sam.h
nobase_include_HEADERS += include/drivers/mv_sam_cio.h
nobase_include_HEADERS += include/drivers/mv_sam_session.h
nobase_include_HEADERS += include/lib/mv_md5.h
nobase_include_HEADERS += include/lib/mv_sha2.h
nobase_include_HEADERS += include/lib/mv_sha1.h

libmusdk_la_SOURCES += drivers/sam/sam.c
libmusdk_la_SOURCES += drivers/sam/sam_hw.c
libmusdk_la_SOURCES += drivers/sam/sam_debug.c
endif
