# LiDAR_A1M8
Hi and welcome to my LiDAR project,
Let's talk about the sensor on which I worked and which may interest you: the LiDAR. It is a sensor that combines angles and distances detections to return a 2D map of the environment. These kinds of sensors are widely used in autonomous cars, vacuum robots, in VR phones too…. In short, a whole bunch of projects, including yours, I’m sure. And now you have to say to yourself:

  But you worked on which model of LiDAR because there’s a whole bunch of them and it’s not easy to find your way around?
  
Being only a student in the 2nd year of engineering school, I am therefore a beginner in this world, so I turned to a basic LiDAR development kit, proposed by SLAMTEC. This kit includes all the elements to take in hand a LiDAR A1M8 (standard model). It can detect points up to 12 meters and capture 4000 points/s!!!

  Okay… So, what’s your project ?

Well, it’s no more or no less than a C-code I developed to communicate with LiDAR.
Inside, you will find the various commands to communicate with the LiDAR and documents useful for understanding the code. I specify that all lines of code are commented to allow you an easy and quick understanding of the operation of LiDAR.

  I see… But do you know that SLAMTEC has github with C++ code that does what you did…. So what’s the point of your project ?

That’s not wrong:) But the code proposed by SLAMTEC is quite complicated. So, if we are talking about a development kit, I thought it’s a pity though, that we don’t understand anything about codes, in order to develop LiDAR on our own projects. My code isn’t finished, there are still things to do on it that I explain at the end of a code. Moreover, the goal of the project is to be able to interface this sensor with a new technology called Luos.

  But, what is Luos ?

Very good question! Luos is an open source API library that allows you to interface various components quickly. Also, no need to waste time with the technical documentation of basic components. Thanks to simple commands, you can easily communicate with the components available in the library. Check it out is really nice:
https://github.com/Luos-io/Examples/tree/master/Projects/l0
And if you are interested in and inspired by the components for projects, check out the documentation that explains in detail how this technology works:
https://docs.luos.io:

  Okay, I get the idea, so what do I need to run your project ?

Very simple, you just need to install the IDE platformIO with the extension VS Code, free of course. You also need Logic2, it’s a free software which allows you to see your data signal during communication. For hardware, you will need a STM32fo discovery development board:
https://www.mouser.fr/ProductDetail/STMicroelectronics/STM32F0DISCOVERY?qs=y%252BFWVGuMvwZK8miFvhZefg==&mgh=1&vip=1
Indeed, I developed my code for STM32f0 microcontroller because it can host Luos. The rest of the things you need are explained in the LiDAR_Code_C_Handling.pdf of my project.

So, feel free if you have any questions, I spent a lot of time with this sensor and I know the difficulties encountered to understand it.

Now let’s develop it !
