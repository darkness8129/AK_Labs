/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include "linux/slab.h"
#include "linux/ktime.h"
#include "asm-generic/bug.h"


MODULE_AUTHOR("Yaroslav Yukhymchuk IV-81");
MODULE_DESCRIPTION("AK-2 Lab 5");
MODULE_LICENSE("Dual BSD/GPL");

static uint number = 1;
module_param(number, uint, S_IRUGO);
MODULE_PARM_DESC(number, "How many times print hello world");

struct own_list_head {
  struct own_list_head *next;
  ktime_t time;
};

static struct own_list_head *head;

static int __init initter(void)
{
  uint i = 0;
  struct own_list_head *p_elem;
  struct own_list_head *c_elem;

  printk(KERN_INFO "number: %d\n", number);

  if (number == 0) {
    printk(KERN_WARNING "Parameter is 0\n");
  } else if (number >= 5 && number <= 10) {
    printk(KERN_WARNING "Parameter is between 5 and 10\n");
  } else if (number > 10) {
    BUG_ON(number > 10);
  }

  if (number > 0) {
    head = kmalloc(
    sizeof(struct own_list_head *),
    GFP_KERNEL
    );

    head->next = NULL;
    head->time = ktime_get();
    printk(KERN_INFO "Hello, world!\n");
  }

  c_elem = head;

  for (i = 1; i < number; i++) {
    p_elem = c_elem;

    c_elem = kmalloc(
    sizeof(struct own_list_head *),
    GFP_KERNEL
    );
    
    if (i == 5) {
      c_elem = NULL;
    }


    c_elem->next = NULL;
    c_elem->time = ktime_get();
    p_elem->next = c_elem;

    printk(KERN_INFO "Hello, world!\n");
  }

  return 0;
}

static void __exit exitter(void)
{
  struct own_list_head *c1 = head;
  struct own_list_head *c2;

  while (c1 != NULL) {
    c2 = c1;

    pr_info("Time: %lld\n", c1->time);

    c1 = c2->next;
    kfree(c2);
  }
}

module_init(initter);
module_exit(exitter);