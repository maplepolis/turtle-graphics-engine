/**
 * CSC A48 - Intro to Computer Science II, Summer 2020
 * 
 * This is the program file where you will implement your solution for
 * assignment 1. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will need to have read the handout carefully. Parts where you have to 
 * implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive and will
 * check that your solution is *correct*, not only that it provides 
 * functionality.
 * 
 * Developed by Mustafa Quraish for CSCA48
 * (c) Mustafa Quraish 2020
 */
#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode {
	char cmd[10];
	int val;
	struct cmdnode *loop_head;
	struct cmdnode *next;

} CmdNode;

/*---------------------------------------------------------------------------*/

int check_cmd(char cmd[10]) {
	if(strcmp(cmd, "penup") == 0 || \
	strcmp(cmd, "pendown") == 0 || \
	strcmp(cmd, "left") == 0 || \
	strcmp(cmd, "right") == 0 || \
	strcmp(cmd, "backward") == 0 || \
	strcmp(cmd, "forward") == 0 || \
	strcmp(cmd, "loop") == 0 || \
	strcmp(cmd, "colour") == 0) {
		return 0;
	}
	
	return -1;
}

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */
   
   if(check_cmd(cmd) != 0) {
	   printf("Invalid command.\n");
	   return NULL;
   }
   
   CmdNode *new_node = (CmdNode *)calloc(1, sizeof(CmdNode));
   strcpy(new_node->cmd, cmd);
   new_node->val = val;
   new_node->next = NULL;
   new_node->loop_head = NULL;
   

  return new_node;
}

/*---------------------------------------------------------------------------*/

int no_val_cmd(char* cmd)
{
	if(strcmp(cmd, "left") == 0 || strcmp(cmd, "right") == 0 || \
	strcmp(cmd, "penup") == 0 || strcmp(cmd, "pendown") == 0){
		return 0;
	}
	return -1;
}
void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */
   
   if(head == NULL)
	   return;

	CmdNode *p = head;
	int counter = 0;
	while(p != NULL){
		if(no_val_cmd(p->cmd) != 0)
			printf("%3d: %s %d\n", counter, p->cmd, p->val);
		else
			printf("%3d: %s\n", counter, p->cmd);
		counter++;
		
		if(strcmp(p->cmd, "loop") == 0)
		{
			CmdNode *q = p->loop_head;
			while(q != NULL)
			{
				if(no_val_cmd(q->cmd) != 0)
					printf("%3d:   %s %d\n", counter, q->cmd, q->val);
				else
					printf("%3d:   %s\n", counter, q->cmd);
				counter++;
				q = q->next;
			}
		}
		p = p->next;
	}
	return;
	
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */
   
	CmdNode *p = head;
	int counter = 0;
	
	while(p != NULL){
		if(no_val_cmd(p->cmd) != 0 && strcmp(p->cmd, cmd) == 0)
			printf("%3d: %s %d\n", counter, p->cmd, p->val);
		else if(no_val_cmd(p->cmd) == 0 && strcmp(p->cmd, cmd) == 0)
			printf("%3d: %s\n", counter, p->cmd);
		counter++;
		
		if(strcmp(p->cmd, "loop") == 0)
		{
			CmdNode *q = p->loop_head;
			while(q != NULL)
			{
				if(no_val_cmd(q->cmd) != 0 && strcmp(q->cmd, cmd) == 0)
					printf("%3d: %s %d\n", counter, q->cmd, q->val);
				else if(no_val_cmd(q->cmd) == 0 && strcmp(q->cmd, cmd) == 0)
					printf("%3d: %s\n", counter, q->cmd);
				counter++;
				q = q->next;
			}
		}
		p = p->next;
	}
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */
   
	if(head == NULL)
	   return 0;
	CmdNode *p = head;
	int counter = 1;
	while(p->next != NULL){
		p = p->next;
		counter++;
		if(strcmp(p->cmd, "loop") == 0 && p->val != 0)
		{
			CmdNode *q = p->loop_head;
			while(q != NULL)
			{
				q = q->next;
				counter++;
			}
		}
	}
  return counter;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */
   
	if(head == NULL)
	{
		head = new_CmdNode;
		return head;
	}
	
	CmdNode *p = head;
	
	while(p->next != NULL){
		p = p->next;
	}
	p->next = new_CmdNode;

  return head;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommandBefore(CmdNode *head, CmdNode *new_CmdNode, int cmdNum) {
  /**
   * This function inserts a new node *before* a given Node in the linked list. 
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to insert new_CmdNode 
   * *before* the corresponding node in the linked list.
   *
   * --------------------------------------------------------------------------
   *  
   * For instance, if your initial list was
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * And you added "pendown" before cmdNum = 2, then you will have
   * 
   *    0: penup
   *    1: forward 200
   *    2: pendown
   *    3: right
   *    4: forward 50
   * 
   * --------------------------------------------------------------------------
   * 
   * If there is no command with the given cmdNum (cmdNum >= list size), 
   * then print "Invalid Command Number.\n" to the screen and *do not* 
   * insert the new node.
   * 
   * Returns a pointer to the head of the linked list with the new node added 
   * into it.
   * 
   * TODO: Implement this function
   */
   
   if(cmdNum == 0)
   {
	   new_CmdNode->next = head;
	   return new_CmdNode;
   }
   
   CmdNode *p = head;
   for(int i = 0; i < cmdNum - 1; i++)
   {
	   if(p->next == NULL)
	   {
		   printf("Invalid Command Number.\n");
		   return head;
	   }
	   else
	   {
		   p = p->next;
	   }
   }
   
   // now p is at the node right before cmdNum
   CmdNode *temp = NULL;
   temp = p->next;
   p->next = new_CmdNode;
   new_CmdNode->next = temp;

  return head;
}

/*---------------------------------------------------------------------------*/

void updateCommand(CmdNode *head, int cmdNum, char cmd[10], int val) {
  /**
   * This function updates a specific node in the linked list based on the 
   * input parameters.
   * 
   * 'cmdNum' is an integer that corresponds to the line number of a command 
   * from the printCommandList() function. Your task is to update the 'cmd' and 
   * 'val' fields of this node.
   * 
   * If there is no command with the given cmdNum, then print 
   * "Invalid Command Number.\n" to the screen, and if 'cmd' is not a correct 
   * command, then print "Invalid command.\n". In both these cases, do *not* 
   * modify the list.
   * 
   * TODO: Implement this function
   */
   
   if(check_cmd(cmd) != 0)
   {
	   printf("Invalid command.\n");
	   return;
   }
   
   CmdNode *p = head;
   for(int i = 0; i < cmdNum; i++)
   {
	   if(p->next == NULL)
	   {
		   printf("Invalid Command Number.\n");
		   return;
	   }
	   else
	   {
		   p = p->next;
	   }
   }
   
   strcpy(p->cmd, cmd);
   p->val = val;

  return;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommand(CmdNode *head, int cmdNum) {
  /**
   * This function deletes the node from the linked list that corresponds to 
   * the line number cmdNum. If there is no command with the given cmdNum, then 
   * the function does nothing.
   * 
   * Returns a pointer to the head of the linked list (which may have changed 
   * as a result of the deletion)
   *
   * TODO: Implement this function
   */
   
	if(cmdNum == 0)
	{
	   CmdNode *temp = head->next;
	   free(head);
	   return temp;
	}
	CmdNode *p = head;
	for(int i = 0; i < cmdNum - 1; i++)
	{
	   if(p->next == NULL)
	   {
		   return head;
	   }
	   else
	   {
		   p = p->next;
	   }
	}
	
	//p is now before the command on cmdNum
	if(p->next->next == NULL) //check if the command->next is a NULL. If so, delete the command on cmdNum and return head
	{
		free(p->next);
		return head;
	}
	else
	{
		CmdNode *after = p->next->next;
		free(p->next);
		p->next = after;
	}

  return head;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */
	if(head == NULL)
		return NULL;
	while(head != NULL)
	{
		CmdNode *temp = head;
		head = head->next;
		
		if(strcmp(temp->cmd, "loop") == 0)
		{
			CmdNode *q = temp->loop_head;
			while(q != NULL)
			{
				CmdNode *looptemp = q;
				q = q->next;
				free(looptemp);
			}
		}
		free(temp);
	}
	return NULL;
}


/*---------------------------------------------------------------------------*/


void insertCommandLoop(CmdNode *input, CmdNode *new_CmdNode)
{

	CmdNode *p = input->loop_head;
	if(p == NULL)
	{
		input->loop_head = new_CmdNode;
		return;
	}
	while(p->next != NULL)
	{
		p = p->next;
	}
	
	p->next = new_CmdNode;
	
}


/*---------------------------------------------------------------------------*/

void get_resulting_position(int startX, int startY, int *resultX, int *resultY, int direction, int direction_modifier, int steps)
{	
	if(direction == 0)
		*resultX = startX + (steps * direction_modifier);
	else if(direction == 2)
		*resultX = startX - (steps * direction_modifier);
	else if(direction == 1)
		*resultY = startY + (steps * direction_modifier);
	else if(direction == 3)
		*resultY = startY - (steps * direction_modifier);
}

void limit_size(int *x, int *y, int maxX, int maxY)
{
	if(*x < 0)
		*x = 0;
	else if(*x > maxX)
		*x = maxX;
	
	if(*y < 0)
		*y = 0;
	else if(*y > maxY)
		*y = maxY;
}
void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   * 
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * We have already implemented a drawLine() function (in imgUtils.c) which 
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */
   
   int currentX = 0;
   int currentY = 0;
   int resultX = 0;
   int resultY = 0;
   int currentcolour = 0;
   int penstat = 0; //0 = down, 1 = up
   int direction = 0; //0 = east ,1 = south ,2 = west ,3 = north
   
   CmdNode *p = head;
   while(p != NULL)
   {
	   if(strcmp(p->cmd, "loop") == 0)
	   {
			for(int i = 0; i < p->val; i++)
			{
				CmdNode *q = p->loop_head;
				while(q != NULL)
				{
				   if(strcmp(q->cmd, "left") == 0)
				   {
					   direction = (direction - 1) % 4;
					   if(direction == -1)
						   direction = 3;
				   }
				   else if(strcmp(q->cmd, "right") == 0)
				   {
					   direction = (direction + 1) % 4;
				   }
				   else if(strcmp(q->cmd, "penup") == 0)
					   penstat = 1;
				   else if(strcmp(q->cmd, "pendown") == 0)
					   penstat = 0;
				   else if(strcmp(q->cmd, "colour") == 0)
				   {
					   currentcolour = q->val;
				   }
				   else if((strcmp(q->cmd, "forward") == 0 || strcmp(q->cmd, "backward") == 0))
				   {
					   int direction_modifier = 1;
					   if(strcmp(q->cmd, "backward") == 0)
						   direction_modifier = -1;
					   get_resulting_position(currentX, currentY, &resultX, &resultY, direction, direction_modifier, q->val);
					   limit_size(&resultX, &resultY, im->sx, im->sy);
					   if(penstat == 0)
						   drawLine(im, currentX, currentY, resultX, resultY, currentcolour);
					   currentX = resultX;
					   currentY = resultY;
				   }
				   q = q->next;
				   
				}
			}
	   }
	   else if(strcmp(p->cmd, "left") == 0)
	   {
		   direction = (direction - 1) % 4;
		   if(direction == -1)
			   direction = 3;
	   }
	   else if(strcmp(p->cmd, "right") == 0)
	   {
		   direction = (direction + 1) % 4;
	   }
	   else if(strcmp(p->cmd, "penup") == 0)
		   penstat = 1;
	   else if(strcmp(p->cmd, "pendown") == 0)
		   penstat = 0;
	   else if(strcmp(p->cmd, "colour") == 0)
	   {
		   currentcolour = p->val;
	   }
	   else if((strcmp(p->cmd, "forward") == 0 || strcmp(p->cmd, "backward") == 0))
	   {
		   int direction_modifier = 1;
		   if(strcmp(p->cmd, "backward") == 0)
			   direction_modifier = -1;
		   get_resulting_position(currentX, currentY, &resultX, &resultY, direction, direction_modifier, p->val);
		   limit_size(&resultX, &resultY, im->sx, im->sy);
		   if(penstat == 0)
			   drawLine(im, currentX, currentY, resultX, resultY, currentcolour);
		   currentX = resultX;
		   currentY = resultY;
	   }
	   p = p->next;
   }
	
	*endX = resultX;
	*endY = resultY;
   

  return;
}

/*---------------------------------------------------------------------------*/
// All done!

/*int main()
{
	int x = 0;
	int y = 0;
	int rx = 0;
	int ry = 0;
	int direction = 2;
	int direction_modifier = -1;
	int steps = 100;
	get_resulting_position(x, y, &rx, &ry, direction, direction_modifier, steps);
	limit_size(&rx, &ry, 255, 255);
	printf("%d, %d", rx, ry);
	return 0;
}*/