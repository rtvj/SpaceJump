/*
 * Project    : Spacejump
 * Author     : Rutvij Karkhanis
 * Course     : Computer Graphics
 * References : Coursework examples
 * 				 www.spacesimulator.net
 * 				 www.student.nada.kth.se/~nv91-gta/OpenGL/examples/explosion.c
 *
 * arrows     : Navigate the spaceship (Left and Right)
 * spacebar   : Jump
 * Enter      : Fire the laser cannon
 * ESC        : Exit
 */

# include "includes.h"

/**********************************************************
 *
 * SUBROUTINE init()
 *
 * Used to initialize OpenGL and to setup our world
 *
 *********************************************************/

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    Load3DS (&object,"spaceship.3ds");

    object.id_texture=LoadBitmap("spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID

    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture==-1)
    {
        printf("Image file: spaceshiptexture.bmp not found\n");
        //MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }
}

/**********************************************************
 *
 * SUBROUTINE SwitchGameplay()
 *
 * Used to switch between the begining and the end of the
 * game
 *
 *********************************************************/

void SwitchGameplay(int i)
{
    glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[i]);

    glPushMatrix();

    glTranslated(0, 0, 0);

    glColor3f(1,1,1);


    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0); glVertex2f(-9,-5);
    glTexCoord2f(1,0.0); glVertex2f(+9,-5);
    glTexCoord2f(1,1); glVertex2f( 9, 5);
    glTexCoord2f(0.0,1); glVertex2f(-9,+5);

    glEnd();

    glutPostRedisplay();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}



/**********************************************************
 *
 * SUBROUTINE Road()
 *
 * Used to draw an infinite road
 *
 *********************************************************/
void Road(double xx, double yy, double zz)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glPushMatrix();
    glTranslated(xx, 0, zz);

    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3d( -200, -30,12000);
    glTexCoord2f(1.0,0.0);
    glVertex3d(200, -30,12000);
    glTexCoord2f(0.0,0.0);
    glVertex3d(200,-30,-12000);
    glTexCoord2f(0.0,1.0);
    glVertex3d(-200,-30, -12000);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

/**********************************************************
 *
 * SUBROUTINE wall()
 *
 * Used to draw wall objects
 *
 *********************************************************/

void wall(double xx, double yy, double zz)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    glPushMatrix();
    glTranslated(xx, 0, zz);

    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    // Front
    glTexCoord2f(1.0, 1.0);
    glVertex3d( -100, -30,-2800);
    glTexCoord2f(1.0,0.0);
    glVertex3d(100, -30,-2800);
    glTexCoord2f(0.0,0.0);
    glVertex3d(100,10,-2800);
    glTexCoord2f(0.0,1.0);
    glVertex3d(-100,10, -2800);

    // Back
    glTexCoord2f(1.0, 1.0);
    glVertex3d(100, -30,-2805);
    glTexCoord2f(1.0,0.0);
    glVertex3d( -100, -30,-2805);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-100,10,-2805);
    glTexCoord2f(0.0,1.0);
    glVertex3d(100,10,-2805);
    // Right
    glTexCoord2f(1.0, 1.0);
    glVertex3d(100, -30,-2800);
    glTexCoord2f(1.0,0.0);
    glVertex3d( 100, -30,-2805);
    glTexCoord2f(0.0,0.0);
    glVertex3d(100,10,-2805);
    glTexCoord2f(0.0,1.0);
    glVertex3d(100,10,-2800);

    // Left
    glTexCoord2f(1.0, 1.0);
    glVertex3d(-100, -30,-2805);
    glTexCoord2f(1.0,0.0);
    glVertex3d( -100, -30,-2800);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-100,10,-2805);
    glTexCoord2f(0.0,1.0);
    glVertex3d(-100,10,-2800);
    // Top
    glTexCoord2f(1.0, 1.0);
    glVertex3d( -100, 10,-2800);
    glTexCoord2f(1.0,0.0);
    glVertex3d(100, 10,-2800);
    glTexCoord2f(0.0,0.0);
    glVertex3d(100,10,-2805);
    glTexCoord2f(0.0,1.0);
    glVertex3d(-100,10, -2805);
    // Bottom
    glTexCoord2f(1.0, 1.0);
    glVertex3d( -100, -30,-2805);
    glTexCoord2f(1.0,0.0);
    glVertex3d(100, -30,-2805);
    glTexCoord2f(0.0,0.0);
    glVertex3d(100,-30,-2800);
    glTexCoord2f(0.0,1.0);
    glVertex3d(-100,-30, -2800);

    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

/**********************************************************
 *
 * SUBROUTINE Background()
 *
 * Used to draw the background planet
 *
 *********************************************************/
static void Background(double D)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, D, D, 0.0, 0.0, 1.f);
    glDepthMask(GL_FALSE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,sky[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1); glVertex2f(0,0);
    glTexCoord2f(1.0,1); glVertex2f(D,0);
    glTexCoord2f(1.0,0); glVertex2f(D,D);
    glTexCoord2f(0,0); glVertex2f(0,D);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

/**********************************************************
 *
 * SUBROUTINE display()
 *
 * This is our main rendering subroutine, called each frame
 *
 *********************************************************/
void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue


    width =  glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);

    glWindowPos2i(width - 100, height - 15);

    if(enter && flag3)
    {
        SwitchGameplay(2);
        glFlush(); // This force the execution of OpenGL commands
        glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
        return;
    }

    Print("Score: %d", score);
    if(over)
    {
        SwitchGameplay(1);
        glFlush(); // This force the execution of OpenGL commands
        glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
        return;
    }
    //  Erase the window and the depth buffer
    glClearColor(0,0.3,0.7,0);


    Background(3.5*dim); // draw space like looking texture
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
    //  Perspective - set eye position
    gluLookAt(Ex,Ey,Ez , Ox,Oy,Oz , Ux,Uy,Uz);



    for ( i = 0; i < NUM_STAR; i++ )
    {
        stars(star[i].x, star[i].y, star[i].z, star[i].a, star[i].b, star[i].c);
    }

    // draw laser cannon if fired
    if(bullet == 1 && space == 1)
    {
        laser_bullet(bx,by,bz,5,5,400);
    }

    // check if spaceship is hit by enemy
    if(px > ex-40 && px < ex+40 && py > ey-40 && py < ey+40 && pz > ez-40 && pz < ez+40 )
    {
        space = 0;
        CreateExplosion ();
        Mix_PlayMusic(blast,0);
        over = 1;
        enemy = 0;
    }
    // Check if spaceship hits the wall
    if(px >= wall_x-100 && px <= wall_x+100 && py >= wall_y-30 && py <= wall_y+10 && pz >= wall_z-100 && pz <= wall_z+100 )
    {
        space = 0;
        CreateExplosion ();
        Mix_PlayMusic(blast,0);
        over = 1;
    }

    // gravity, check if the spaceship fell off the road
    if( (px > 200 || px < -200) )
    {
        py -= 5;

        if( py < -40)
        {
            space = 0;
            gravity = 1;
            CreateExplosion ();
            Mix_PlayMusic(blast,0);
            over = 1;
        }
    }


    if(space)
    spaceship(px, py, pz, -90+up, side, 180,0.85,0.85,0.85);

    if(enemy == 1)
    spaceship(ex, ey, ez, -90, 0, 0,1,1,1);

    glLoadIdentity();
    glTranslatef(fx,fy,fz);

    if (fuel > 0)
    {
        glPushMatrix ();

        glBegin (GL_POINTS);

        for (i = 0; i < NUM_PARTICLES; i++)
        {
            glColor3fv (particles[i].color);
            glVertex3fv (particles[i].position);
        }

        glEnd ();

        for (i = 0; i < NUM_DEBRIS; i++)
        {
            glPushMatrix ();

            glTranslatef (debris[i].position[0],
            debris[i].position[1],
            debris[i].position[2]);

            glRotatef (debris[i].orientation[0], 1.0, 0.0, 0.0);
            glRotatef (debris[i].orientation[1], 0.0, 1.0, 0.0);
            glRotatef (debris[i].orientation[2], 0.0, 0.0, 1.0);

            glScalef (debris[i].scale[0],
            debris[i].scale[1],
            debris[i].scale[2]);

            glBegin (GL_TRIANGLES);
            glColor3f(((float) rand ()) / ((float) RAND_MAX), ((float) rand ()) / ((float) RAND_MAX), 0.3);
            glVertex3f (0.0, 0.5, 0.0);
            glVertex3f (-0.25, 0.0, 0.0);
            glVertex3f (0.25, 0.0, 0.0);
            glEnd ();

            glPopMatrix ();
        }
    }


    Road(road_x, road_y, road_z);
    wall(wall_x, wall_y, wall_z);

    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer


    flag3++;
}


/**********************************************************
 *
 * SUBROUTINE LoadBitmap()
 *
 * Used to load the bmp image
 *
 *********************************************************/

int LoadBitmap(char *filename)
{
    //printf("loadbitmap\n");
    FILE * file;
    char temp;
    long i;
	size_t size;

    BITMAPINFOHEADER infoheader;

    num_texture++; // The counter of the current texture is increased

    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    size = fread(&infoheader.biWidth, sizeof(int), 1, file);

    size = fread(&infoheader.biHeight, sizeof(int), 1, file);

    size = fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
    //printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
        return 0;
    }

    // read the bpp
    size = fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
     // printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
        return 0;
    }


    fseek(file, 24, SEEK_CUR);

    // read the data.
    infoheader.data = (char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader.data == NULL) {
    // printf("Error allocating memory for color-corrected image data\n");
        return 0;
    }

    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
        //fprintf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = infoheader.data[i];
        infoheader.data[i] = infoheader.data[i+2];
        infoheader.data[i+2] = temp;
    }


    fclose(file); // Closes the file stream


    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);
    size = size + 1;
    free(infoheader.data); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}



/**********************************************************
 *
 * SUBROUTINE resize(int,int)
 *
 * This routine must be called everytime we resize our window.
 *
 *********************************************************/

void resize (int width, int height)
{
    screen_width=width; // We obtain the new screen width values and store it
    screen_height=height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

/**********************************************************
 *
 * SUBROUTINE keyboard(unsigned char,int,int)
 *
 * Used to handle the keyboard input (ASCII Characters)
 *
 *********************************************************/

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;

        case 13:
            if(bullet)
            break;
            Mix_PlayMusic(blt,0);
            bullet = 1;
            bx = px;
            by = py-20;
            bz = pz-100;
            break;
            break;
        case 'x':
        case 'X':
            enter = 0;
            break;

        case 'r':
        case 'R':
            score = 0;
            over = 0;
            enemy = 1;
            space = 1;
            px = 0;
            py = -10;
            break;

        case ' ':
            if(jump)
                    break;
            jump = 1;
            break;
    }

    th %= 360;
    ph %= 360;
    mover(-1);
}



/**********************************************************
 *
 * SUBROUTINE keyboard(int,int,int)
 *
 * Used to handle the keyboard input (not ASCII Characters)
 *
 *********************************************************/

void keyboard_s (int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_F1:
            ll = ll - 50;
            break;

        case GLUT_KEY_F2:
            ll = ll + 50;
            break;

        case GLUT_KEY_F3:
            CreateExplosion();
            break;

        case GLUT_KEY_LEFT:
            px = px - 10;
            if(side > -30)
            side = side - 2;
            break;

        case GLUT_KEY_RIGHT:
            px = px + 10;
            if(side < 30)
            side = side + 2;
            break;

        case GLUT_KEY_PAGE_UP:
            pz = pz + 50;
            break;

        case GLUT_KEY_PAGE_DOWN:
            pz = pz - 50;
            break;
            break;

    }
}

/**********************************************************
 *
 * SUBROUTINE laser_bullet()
 *
 * Used to draw the laser cannon shot
 *
 *********************************************************/

void laser_bullet(double x,double y,double z, double dx,double dy,double dz)
{
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);

    glScaled(dx,dy,dz);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(1,1,0);
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(1,1,0);
    glVertex3f(+1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,+1,-1);
    glVertex3f(+1,+1,-1);
    //  Right

    glColor3f(1,1,0);
    glVertex3f(+1,-1,+1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,+1,-1);
    glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(1,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,+1);
    glVertex3f(-1,+1,+1);
    glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(1,1,0);
    glVertex3f(-1,+1,+1);
    glVertex3f(+1,+1,+1);
    glVertex3f(+1,+1,-1);
    glVertex3f(-1,+1,-1);
    //  Bottom

    glColor3f(1,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,-1,+1);
    glVertex3f(-1,-1,+1);
    //  End
    glEnd();
    //  Undo transofrmations
    glPopMatrix();
}


/**********************************************************
 *
 * SUBROUTINE spaceship()
 *
 * Used to draw the spaceship object from the vertices
 *
 *********************************************************/
void spaceship(double px, double py, double pz,	double dx, double dy, double dz,	double sx, double sy, double sz)
{
    int l_index;

    glPushMatrix();

    glTranslated(px,py,pz);

    glScaled(sz,sy,sy);

    rotation_x = dx;
    rotation_y = dy;
    rotation_z = dz;

    glRotatef(rotation_x,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
    glRotatef(rotation_y,0.0,1.0,0.0);  //
    glRotatef(rotation_z,0.0,0.0,1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)

    for (l_index=0;l_index<object.polygons_qty;l_index++)
    {
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
        object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
        object.vertex[ object.polygon[l_index].a ].y,
        object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
        object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
        object.vertex[ object.polygon[l_index].b ].y,
        object.vertex[ object.polygon[l_index].b ].z);

        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
        object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
        object.vertex[ object.polygon[l_index].c ].y,
        object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/**********************************************************
 *
 * SUBROUTINE Init_star()
 *
 * Used to initialize random star particles
 *
 *********************************************************/
void Init_star()
{
    int i;

    for (i = 0; i < NUM_STAR; i++)
    {
        star[i].x = -300 + (rand() % 601);
        star[i].y = -200 + (rand() % 401);
        //star[i].z = -100000 + (rand() % 200001);
        star[i].z = -6000 + 30*i;

        star[i].a = (float) rand () / ((float) RAND_MAX);
        star[i].b = 0;
        star[i].c = (float) rand () / ((float) RAND_MAX);

    }
}

/**********************************************************
 *
 * SUBROUTINE stars()
 *
 * Used to draw the star objects
 *
 *********************************************************/
void stars(double x, double y, double z, float a, float b, float c)
{
    glPushMatrix();
    glPointSize( 3.0 );
    glTranslated(x,y,z);
    glBegin (GL_POINTS);

    glColor3f (a,b,2.0*c);
    glVertex3f (0.0,0.0,0.0);

    glEnd ();
    glPopMatrix();
}


/**********************************************************
 *
 * SUBROUTINE mover()
 *
 * Used to used  to move the movable objects at a set interval
 *
 *********************************************************/
void mover(int toggle)
{

    int i;

    update_animation();

    // move stars
    for ( i = 0; i < NUM_STAR; i++ )
    {
        if(star[i].z > 3000)
        {
            star[i].z = -6000;
            star[i].x = -3000 + (rand() % 6001);
            star[i].y = -2000 + (rand() % 4001);
        }
        star[i].z = star[i].z + 40;
    }
    if(jump)
    {
        if(py < 100)
        {
            py += 10;
            descend = 0;
        }
        else
        {
            jump = 0;
            descend = 1;
        }
    }

    if(descend)
    {
        if(py > -10)
        {
            py -= 10;
            jump = 0;
        }
        else
        {
            descend = 0;
            jump = 0;
        }
    }

    // move enemy
    ez = ez + 50;

    if(ez > 3000)
    {
        ez = -6000;
        ex = (rand() % 201);
        ey = -10;
    }

    // move road
    road_z += 40;


    if(road_z > 6000)
    {
        road_z = -6000;
        road_x = 0;
        road_y = 0;

    }

    //move wall make sure that enemy and the walls don't collide
    wall_z  += 40;

    if(wall_z > 3500)
    {
        wall_z = -6000;
        wall_x = (ex + rand()) % 201;
        wall_y = -10;

    }
    // move bullet and check for kill

    if(bullet == 1 && space == 1)
    {
        bz = bz - 300;
        if(bz < -7000) bullet = 0;

        //check if bullet hit enemy spaceship
        if(bx > ex-prs && bx < ex+prs && by > ey-prs && by < ey+prs && bz > ez-200 && bz < ez+200 )
        {
            fx = 0;
            fy = 0;
            fz = -12;
            ez = 4000;
            // make explosion if hit by bullet
            flag1++;
            if(flag2 - flag1 > 20)
            {
                CreateExplosion ();
                Mix_PlayMusic(blast,0);
                score = score + 100;
                flag1 = 0;
                flag2 = 1;
            }
        }
    }

    flag2++;

    //  Toggle movement
    if (toggle>0)
    move = !move;
    //  Increment light position
    else
    zh = (zh+5)%360;

    if(side < 0) side = side + 1;
    if(side > 0) side = side - 1;

    if(up < 0) up = up + 1;
    if(up > 0) up = up - 1;

    //  Animate flight using Lorenz transform
    Ex = -2*dim*Sin(th)*Cos(ph);
    Ey = +2*dim        *Sin(ph);
    Ez = +2*dim*Cos(th)*Cos(ph);
    Ox = Oy = Oz = 0;
    X = Y = Z = 0;
    Dx = 1; Dy = 0; Dz = 0;
    Ux = 0; Uy = 1; Uz = 0;

    //  Set timer to go again
    if (move && toggle>=0) glutTimerFunc(50,mover,0);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}


/**********************************************************
 *
 * SUBROUTINE filelength()
 *
 * Used to calculate the filesize
 *
 *********************************************************/
long filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}



/**********************************************************
 *
 * SUBROUTINE Load3DS()
 *
 * Used to read a 3DS file and get the information on the
 * vertices of the 3D object
 *
 *********************************************************/
char Load3DS (obj_type_ptr p_object, char *p_filename)
{
    int i; //Index variable
    size_t size;
    FILE *l_file; //File pointer

    unsigned short l_chunk_id; //Chunk identifier
    unsigned int l_chunk_lenght; //Chunk lenght

    unsigned char l_char; //Char variable
    unsigned short l_qty; //Number of elements in each chunk

    unsigned short l_face_flags; //Flag that stores some face information

    if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

    while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
    {
        size = fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
        //printf("ChunkID: %x\n",l_chunk_id);
        size = fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
        //printf("ChunkLenght: %x\n",l_chunk_lenght);

        switch (l_chunk_id)
        {
            case 0x4d4d:
                break;

            case 0x3d3d:
                break;

            case 0x4000:
                i=0;
                do
                {
                    size = fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
                    i++;
                }while(l_char != '\0' && i<20);
                break;

            case 0x4100:
                break;

            case 0x4110:
                size = fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;
                //printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
                    size = fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
                    //printf("Vertices list x: %f\n",p_object->vertex[i].x);
                    size = fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
                    //printf("Vertices list y: %f\n",p_object->vertex[i].y);
                    size = fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
                    //printf("Vertices list z: %f\n",p_object->vertex[i].z);
                }
                break;

            case 0x4120:
                size = fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;
                //printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
                    size = fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point a: %d\n",p_object->polygon[i].a);
                    size = fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point b: %d\n",p_object->polygon[i].b);
                    size = fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point c: %d\n",p_object->polygon[i].c);
                    size = fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
                    //printf("Face flags: %x\n",l_face_flags);
                }
                break;

            case 0x4140:
                size = fread (&l_qty, sizeof (unsigned short), 1, l_file);
                for (i=0; i<l_qty; i++)
                {
                    size = fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
                    //printf("Mapping list u: %f\n",p_object->mapcoord[i].u);
                    size = fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
                    //printf("Mapping list v: %f\n",p_object->mapcoord[i].v);
                }
                break;

            size = size + 1;
            default:
                fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
    }
    fclose (l_file); // Closes the file stream
    return (1); // Returns ok
}


/**********************************************************
 *
 * SUBROUTINE Reverse()
 *
 * Used for platform based compatibility (little endian/big endian)
 *
 *********************************************************/
static void Reverse(void* x,const int n)
{
    int k;
    char* ch = (char*)x;
    for (k=0;k<n/2;k++)
    {
        char tmp = ch[k];
        ch[k] = ch[n-1-k];
        ch[n-1-k] = tmp;
    }
}


/**********************************************************
 *
 * SUBROUTINE LoadTexBMP()
 *
 * Used to texture from bmp files
 *
 *********************************************************/
unsigned int LoadTexBMP(const char* file)
{
    unsigned int   texture;    // Texture name
    FILE*          f;          // File pointer
    unsigned short magic;      // Image magic
    unsigned int   dx,dy,size; // Image dimensions
    unsigned short nbp,bpp;    // Planes and bits per pixel
    unsigned char* image;      // Image data
    unsigned int   k;          // Counter
    int            max;        // Maximum texture dimensions

    //  Open file
    f = fopen(file,"rb");
    if (!f) Fatal("Cannot open file %s\n",file);
    //  Check image magic
    if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
    if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
    //  Seek to and read header
    if (fseek(f,16,SEEK_CUR) || fread(&dx ,4,1,f)!=1 || fread(&dy ,4,1,f)!=1 ||
    fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
    Fatal("Cannot read header from %s\n",file);
    //  Reverse bytes on big endian hardware (detected by backwards magic)
    if (magic==0x424D)
    {
        Reverse(&dx,4);
        Reverse(&dy,4);
        Reverse(&nbp,2);
        Reverse(&bpp,2);
        Reverse(&k,4);
    }
    //  Check image parameters
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max);
    if (dx<1 || dx>max) Fatal("%s image width %d out of range 1-%d\n",file,dx,max);
    if (dy<1 || dy>max) Fatal("%s image height %d out of range 1-%d\n",file,dy,max);
    if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
    if (bpp!=24) Fatal("%s bits per pixel is not 24: %d\n",file,bpp);
    if (k!=0)    Fatal("%s compressed files not supported\n",file);
#ifndef GL_VERSION_2_0
    //  OpenGL 2.0 lifts the restriction that texture size must be a power of two
    for (k=1;k<dx;k*=2);
    if (k!=dx) Fatal("%s image width not a power of two: %d\n",file,dx);
    for (k=1;k<dy;k*=2);
    if (k!=dy) Fatal("%s image height not a power of two: %d\n",file,dy);
#endif

    //  Allocate image memory
    size = 3*dx*dy;
    image = (unsigned char*) malloc(size);
    if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",size,file);
    //  Seek to and read image
    if (fseek(f,20,SEEK_CUR) || fread(image,size,1,f)!=1) Fatal("Error reading data from image %s\n",file);
    fclose(f);
    //  Reverse colors (BGR -> RGB)
    for (k=0;k<size;k+=3)
    {
        unsigned char temp = image[k];
        image[k]   = image[k+2];
        image[k+2] = temp;
    }

    //  Sanity check
    ErrCheck("LoadTexBMP");
    //  Generate 2D texture
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    //  Copy image
    glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    if (glGetError()) Fatal("Error in glTexImage2D %s %dx%d\n",file,dx,dy);
    //  Scale linearly when image size doesn't match
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //  Free image memory
    free(image);
    //  Return texture name
    return texture;
}




/**********************************************************
 *
 * SUBROUTINE update_animation()
 *
 * Used to initialize animation variables
 *
 *********************************************************/
void update_animation(void)
{
    int i;

    if (!wantPause)
    {
        if (fuel > 0)
        {
            for (i = 0; i < NUM_PARTICLES; i++)
            {
                particles[i].position[0] += particles[i].speed[0] * 0.2;
                particles[i].position[1] += particles[i].speed[1] * 0.2;
                particles[i].position[2] += particles[i].speed[2] * 0.2;
            }

            for (i = 0; i < NUM_DEBRIS; i++)
            {
                debris[i].position[0] += debris[i].speed[0] * 0.1;
                debris[i].position[1] += debris[i].speed[1] * 0.1;
                debris[i].position[2] += debris[i].speed[2] * 0.1;

                debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
                debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
                debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
            }

            --fuel;
        }

        angle += 0.3;  /* Always continue to rotate the camera */
    }

    glutPostRedisplay ();

}




/**********************************************************
 *
 * SUBROUTINE CreateExplosion()
 *
 * Used to create a new explosion
 *
 *********************************************************/
void CreateExplosion (void)
{
    int i;

    for (i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].position[0] = 0.0;
        particles[i].position[1] = 0.0;
        particles[i].position[2] = 0.0;

        particles[i].color[0] = 1.0;
        particles[i].color[1] = 1.0;
        particles[i].color[2] = 0.0;

        Speed (particles[i].speed);
    }

    for (i = 0; i < NUM_DEBRIS; i++)
    {
        debris[i].position[0] = 0.0;
        debris[i].position[1] = 0.0;
        debris[i].position[2] = 0.0;

        debris[i].orientation[0] = 0.0;
        debris[i].orientation[1] = 0.0;
        debris[i].orientation[2] = 0.0;

        debris[i].color[0] = 1.0;
        debris[i].color[1] = 1.0;
        debris[i].color[2] = 0.0;

        debris[i].scale[0] = (2.0 *
        ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
        debris[i].scale[1] = (2.0 *
        ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
        debris[i].scale[2] = (2.0 *
        ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

        Speed (debris[i].speed);
        Speed (debris[i].orientationSpeed);
    }

    fuel = 100;
}




/**********************************************************
 *
 * SUBROUTINE Speed()
 *
 * Used to Randomize a new speed vector.
 *
 *********************************************************/
void Speed (float dest[3])
{
    float    x;
    float    y;
    float    z;
    float    len;

    x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
    y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
    z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

    /*
    * Normalizing the speed vectors gives a "fireball" effect
    *
    */

    if (wantNormalize)
    {
        len = sqrt (x * x + y * y + z * z);

        if (len)
        {
            x = x / len;
            y = y / len;
            z = z / len;
        }
    }

    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/**********************************************************
 *
 * The main routine
 *
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("SpaceJump");
    glutFullScreen();
    glutDisplayFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    mover(1);
    sky[0] = LoadTexBMP("planetcropped_scaled_trans.bmp");
    texture[0] = LoadTexBMP("floor2.bmp");
    texture[1] = LoadTexBMP("over.bmp");
    texture[2] = LoadTexBMP("spacejump_start.bmp");
    texture[3] = LoadTexBMP("brickwall.bmp");

    //  Initialize audio
    if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) Fatal("Cannot initialize audio\n");

    blt = Mix_LoadMUS("bullet.ogg");

    if (!blt) Fatal("Cannot load bullet.ogg\n");

    eng = Mix_LoadMUS("engine.ogg");

    if (!eng) Fatal("Cannot load engine.ogg\n");

    blast = Mix_LoadMUS("explosion.ogg");

    if (!blast) Fatal("Cannot load explosion.ogg\n");

    Init_star();
    init();


    width =  glutGet(GLUT_WINDOW_WIDTH);
    height = glutGet(GLUT_WINDOW_HEIGHT);

    glutMainLoop();

    return(0);
}
