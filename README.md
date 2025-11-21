UART dual board RX-TX.

TX(master): NVIC settings-gloabal interrupt enabled. DMA settings activated in usart2.

RecivetoIdle RX(slave): NVIC settings-gloabal interrupt enabled. DMA settings activated in usart2. RX pin is pull-down.

timer settings for master, TIM3 activated, clock source is internal clock, TIM3 gloabal interrupt enabled, prescaler:8400-1, Counter Period: 10000-1.
