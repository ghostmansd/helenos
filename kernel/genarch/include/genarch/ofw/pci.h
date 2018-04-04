/*
 * Copyright (c) 2006 Jakub Jermar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef KERN_PCI_H_
#define KERN_PCI_H_

#include <genarch/ofw/ofw_tree.h>
#include <typedefs.h>
#include <ddi/irq.h>
#include <typedefs.h>

typedef struct {
	/* Needs to be masked to obtain pure space id */
	uint32_t space;

	/* Group phys.mid and phys.lo together */
	uint64_t addr;
	uint64_t size;
} __attribute__((packed)) ofw_pci_reg_t;

typedef struct {
	uint32_t space;

	/* Group phys.mid and phys.lo together */
	uint64_t child_base;
	uint64_t parent_base;
	uint64_t size;
} __attribute__((packed)) ofw_pci_range_t;

extern bool ofw_pci_apply_ranges(ofw_tree_node_t *, ofw_pci_reg_t *,
    uintptr_t *);

extern bool ofw_pci_reg_absolutize(ofw_tree_node_t *, ofw_pci_reg_t *,
    ofw_pci_reg_t *);

extern bool ofw_pci_map_interrupt(ofw_tree_node_t *, ofw_pci_reg_t *,
    int, int *, cir_t *, void **);

#endif
