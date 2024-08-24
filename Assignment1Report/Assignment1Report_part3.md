# Assignment 1: Part 3:
### 1) A picture of the output:

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/4_w_l.png)

### 2) 

### 3)

### 4) changes in camera, renderer and main: 
### camera: I introduced set characteristic of rotate and translate to us them in the Gui, also  added set inverse that doing inverse to predominant mat, in additoin
### to get inverse that I use at renderer to draw the model. set perspective and set ortho is also for the Gui to use when the projection is ortho 
### or perspective. I also added set ortho flag and get to know which projection I did (I give this flag 1 in set ortho and 0 in set perspective), 
### the last function that I added is Getlookat that returns the value of look at matrix that I calculate in SetCameraLookAt function.
### Renderer: How the model will be drawn? defining inverse, projection, lookat and transformation matrices to multiple them with the vector to draw 
### every face, the only different between ortho and perspective in drawing is that we didn't divides on w in ortho projection.
### main: I updated the Render function to appropriate the drawing with the actions done on the camera and not just on the model,I multiplied by the inverse of the transformation matrix of the camera and the lookAt matrix and the projection matrix in addition to the scale_translate matrix to so we can see the model.the order of the matrices multiplication: a1 = scale_translate * proj * lookAt_mat * inversmat * Transformation_mat * glm::vec4(scene.GetActiveModel().GetVer(I1), 1);
### set ortho for ortho button and set angle for perspective button, for the lookat I introduced the buttons of eye, at and up every one fpr X,Y,Z and perform set examine on them.
### ![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/4_l_w.png)
### 
![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/4_w_l.png)

### 5) * load model :* dolly (changing the center of the viewpoint, moving the camera closer to the model)* changing the zoom (changing the fovy- scale-):
![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/5_1.png)

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/5_2.png)

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/5_3.png)

### 6)   I have to do translate to see the changes, and the difference between the rotate in cameras frame vs worlds frame: 
   * Translate world, Rotate camera:![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/6_orth.png)

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/6_pers.png)

### 7) A picture with eye vector (11,11,11):

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/7_1.png)

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/7_2_zoom%2Btrans.png)

### 8) 

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/8_l.png)

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/8_w.png)

### 9)
 
### 10)
 
### 11)
 
### 12) 

![*](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_3/12_gui.png)


