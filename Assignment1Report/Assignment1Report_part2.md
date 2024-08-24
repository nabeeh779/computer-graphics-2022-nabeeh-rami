# Assignment 1 part b
#### *
as a way to  go through  all the faces and all their vertices,  
I brought  features to the MeshModel class  which might be:  
print_faces () and- print_vers (),
the primary  goes  via  all the faces (within the faces vector that is  within the MeshMoudel magnificence), and then with the help of the GetVertexIndex method  this is  within the face elegance, we can  recognise the index of the vertices after which  realize the coordinates through the Victor of The vertices which can be  inside theMeshModel elegance.

#### *
on the way to scale and translate the vertices such that they'll  in shape  within the window,I need to trade  a pieceinside the LoadMeshModel function  this is  inside the Utils magnificence, when loading the model (inside the  at the same time as loop), I preserve the maximum and minimal X and the identical for Y and Z,  
and on the  quit I hold the most of: x_max, y_max, z_max  
So i can do the proper scale (divide with the aid of  most)  
after which do translate with vector (abs (x_min), abs (y_min), abs (z_min)), so that every one  factors are morethan 0.  
And at the  end the multiplier of the matrices generated via  the size and translate operation is included  within thesheard_ptr that back from the function (here we replace the MeshModel constructor to include a 4x4 matrix).

#### *
For this section, I delivered  methods (to the MeshModel elegance) one to get right of entry to the matrix of the version that we loaded, and the second is to get entry to the vector of the vertex in specific index,  
within the Render function  we will  get admission to this matrix after which  undergo  all the faces and make a 4vec (in the hom.cords) , with the aid of  more than one the matrix through the vectors (of a specific vertex of the face (there are three vertices)), and in the long run we draw the strains that connect the coordinates of the vectors (4vecs).

###### the code:
void Renderer::Render(const Scene& scene) {

	int I1, I2, I3;
	glm::vec4 a1, b1, c1;
	glm::mat4x4 mymat;
	glm::mat4x4 Tmat;
	glm::ivec3 color(2, 1, 1);
	if (scene.GetModelCount()) {
		auto model = scene.GetActiveModel();
		mymat = model->GetM();
		Tmat = model->get_Transform_Mat();
		mymat = Tmat * mymat;
		for (int i = 0; i < model->GetFacesCount(); i++) 
		{
			I1 = model->GetFace(i).GetVertexIndex(0);
			I2 = model->GetFace(i).GetVertexIndex(1);
			I3 = model->GetFace(i).GetVertexIndex(2);

			a1 = mymat * glm::vec4(model->GetVer(I1), 1);
			b1 = mymat * glm::vec4(model->GetVer(I2), 1);
			c1 = mymat * glm::vec4(model->GetVer(I3), 1);
			DrawLine(glm::ivec2(a1.x / a1.w, a1.y / a1.w), glm::ivec2(b1.x / b1.w, b1.y / b1.w), color);
			DrawLine(glm::ivec2(a1.x / a1.w, a1.y / a1.w), glm::ivec2(c1.x / c1.w, c1.y / c1.w), color);
			DrawLine(glm::ivec2(b1.x / b1.w, b1.y / b1.w), glm::ivec2(c1.x / c1.w, c1.y / c1.w), color);
		}
		
	}
	
}

#### *
For this segment I added a 13 4x4 matrices, for every  form of transformation (one for the world  body and the second for the nearby  frame), and two for each rotation around  each axis (6 matrices), and one matrix for the multiply of the matrices of the various  types of  adjustments, and additionally we outline  eight new methods to set those matrices(the techniques to set the rotation of every axis have been  covered in 2 strategies) and one technique to get the final matrix (the transformation matrix).  
After load a version, the consumer can trade the body of transformation by  click  on the button "exchange  frame" , after which  we are able to  pick out a sort of transformation and see the consequences. by  selecting  a specific  typewe make a trade  at the transformation matrix that we described  on the MeshModel class  by means of use the precise  method.

#### *
to expose the effects of the adjustments  on the  model we ought to  a couple of  the main matrix of the loaded version  by way of the transformation matrix that we replace  in step with the user  alternatives, and then  retain  to draw the model as showed in segment (three).

###### pictures 

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_2/1.jpeg)

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_2/2.jpeg)

![](https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/screenshots/A_2/3.jpeg)


