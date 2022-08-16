#ifndef _LED_H
#define _LED_H

#include "sys.h"
#include "common.h"

#define LED0 PCout(13)

void led_init(void);

#endif
