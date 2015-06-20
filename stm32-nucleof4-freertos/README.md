# STM32Nucleo-F4 FreeRTOS example
This example project shows how to start programming with FreeRTOS on a STM32Nucleo board. The project is a simple app with two tasks: one of this waits until the user presses the blue button on the Nucleo; when this happens, it wakes up the other task locked on a semaphore; this task will start blinking the green LED forever.

It was generated in Eclipse using [GNU ARM Eclipse](http://gnuarmeclipse.livius.net/blog/) by Liviu Ionescu. If you need to setup the whole Eclipse/GCC ARM tool-chain, you can follow [this series](http://www.carminenoviello.com/en/2014/12/28/setting-gcceclipse-toolchain-stm32nucleo-part-1/) made of three parts on my blog.

If you are interested in knowing the full story under this project (how to generate the project, to import FreeRTOS, etc), I wrote a tutorial on [my blog](http://www.carminenoviello.com/en/2015/06/22/running-freertos-stm32nucleo-free-gcceclipse-toolchain/ ).

**The example is preconfigured to work with Nucleo-F401RE board.**