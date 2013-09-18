#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INFINITY 2048 * 2048

void solve(int pnum, int source, int destin, int weight[30][30]);
void menu();
int check_visited();

int weight[30][30], weight_cpy[30][30], plist[30], print_weights[100], print_count = 0, sum = 0, n;
int finished[30], citycount = 0, all_visited = 0, visited_arr[30], first_flag = 1;
long fdist[30];
char list[30][30], print_nodes[100][30];

int main(int argc, char *argv[])
{

   char input, buffer[1028], cmpbuf[1028];
   FILE *dfile, *pfile;
   int i = 0, j, b, t, p = 0, k = 0, m = 0, extra; 
   int spcount = 0, line = 1, pnum, found = 0; 
   int cityX, cityY, dist, s, d, nextdest, nextsource, shortest_path = INFINITY;

   if(argc < 2) {
	  printf("Error!! No datafile given\n");
	  return 1;
   } else {
	  dfile = fopen(argv[1], "r");
   }

   if(argc == 3) 
	 pfile = fopen(argv[2], "r");
   else
      pfile = stdin;

   if(!dfile) {
      printf("Error: datafile did not open!\n");
	  return 1;
   }

   if(!pfile) {
	  printf("Error: problemfile did not open!\n");
	  return 1;
   }

   // memset to remove garbage chars 
   memset(list, '\0', sizeof(list));
   memset(plist, '\0', sizeof(plist));
   memset(weight, '\0', sizeof(weight));

   if(dfile) {
      while((input = fgetc(dfile)) != EOF) {
	     if(input == '\n') {
			switch(line)
			{
			   case 1:
				  // check N > 0
				  n = atoi(buffer);
                  if(n <= 0) {
					 printf("Error!! datafile line 1, N <= 0\n");
					 exit(EXIT_FAILURE);
				  }
			      break;
               case 2:
				  buffer[i] = ' ';
				  j = 0;
				  while(buffer[j]) {
					 if(isspace(buffer[j])) {
						citycount++;
						list[k][m] == '\0';
						k++;
						m = 0;
                     } else {
						list[k][m] = buffer[j];
						m++;
					 }
                     j++;
                  }
				  // check N strings are listed
				  if(n != citycount) {
					 printf("Error!! datafile line 2, N != strings listed\n");
					 exit(EXIT_FAILURE);
				  }
				  break; 
               default:
				  // all other lines will check cities are in list
				  m = 0;
			      for(j = 0; j <= strlen(buffer); j++) {
					 if(buffer[j] == '\0') {
						dist = atoi(cmpbuf);
						if(weight[cityY][cityX] > 0 &&  dist > weight[cityY][cityX]) {
						   spcount = 0;
						   memset(cmpbuf, '\0', sizeof(cmpbuf));
						   break;
						}
						weight[cityY][cityX] = dist;
						weight[cityX][cityY] = dist;
						spcount = 0;
						memset(cmpbuf, '\0', sizeof(cmpbuf));
						break;
					 }
					 if(isspace(buffer[j])) {
						for(b = 0; b <= k; b++) {
						   if(strcmp(cmpbuf, list[b]) == 0) {
							  if(spcount == 0)
								 cityY = b;

							  if(spcount == 1)
								 cityX = b;
							  break;
						   }
                         
						   if(b == k) {
							  printf("Error!! on line:%d, city:%s not in list!\n", line, cmpbuf);
							  exit(EXIT_FAILURE);
						   }


						}
						memset(cmpbuf, '\0', sizeof(cmpbuf));
                        m = 0;
						spcount++;
					 } else {
						cmpbuf[m] = buffer[j];
						m++; 
					 }
				  }
			      break;
		    }
			memset(buffer, '\0', sizeof(buffer));
			memset(cmpbuf, '\0', sizeof(cmpbuf));
			i = 0;
			line++;

		 } else { 
		 buffer[i] = tolower(input);
		 i++;
		 }
      }
   }

   memset(buffer, '\0', sizeof(buffer));
   memset(cmpbuf, '\0', sizeof(cmpbuf));
   fclose(dfile);

   if(pfile) {

	  menu();


	  i = 0;
	  while((input = fgetc(pfile)) != EOF) {
		 if(input == '\n') {

			cmpbuf[0] = buffer[0];
			pnum = atoi(cmpbuf);
			memset(cmpbuf, '\0', sizeof(cmpbuf));

			j = 2;
			m = 0;
            while(1) {
			   if(isspace(buffer[j]) || buffer[j] == '\0') {
				  for(t = 0; t < n; t++) {
				     if(strcmp(cmpbuf, list[t]) == 0) {
						plist[p] = t;
						p++;
						break;
					 }

					 if(t == n - 1) {
					    printf("Error!! in problemfile, city:%s not in datafile\n", cmpbuf);
					    exit(EXIT_FAILURE);
					 }
                  }
                  memset(cmpbuf, '\0', sizeof(cmpbuf));
				  j++;
				  m = 0;

				  if(buffer[j] == '\0')
					 break;
			   } else {
			      cmpbuf[m] = buffer[j];
			      m++;
			      j++;
			   }
			}

            switch(pnum)
			{
			   case 1:
				   // Problem 1
				   // calls solve() (Dijkstra's algo) to find shortest path
				   // from source to each node
				  printf("RESPONSE:\n");
				  solve(pnum, plist[0], plist[1], weight);
				  printf("\n");
				  break;
               case 2:
				  //Problem 2
				  // calls solve() for each node given, 
				  // updates source node each time
				  printf("RESPONSE:\n");
				  for(j = 0; j < p - 1; j++) {
				     solve(pnum, plist[j], plist[j+1], weight);
					 first_flag = 0;
				  }
				  // prints output of path we took
				  printf("%d ", sum);
				  for(j = 0; j <= print_count; j++) {
					 if(print_nodes[j])
						printf("%s", print_nodes[j]);
                     if(print_weights[j])
						printf(" %d ", print_weights[j]);
				  }
				  printf("\n");
				  memset(print_nodes, '\0', sizeof(print_nodes));
				  memset(print_weights, '\0', sizeof(print_weights));
				  sum = 0;
				  print_count = 0;
				  first_flag = 1;
				  break;
               case 3:
				  //Problem 3
				  //does same as Problem 2 but
				  //goes through all nodes
				  printf("RESPONSE:\n");
				  nextsource = plist[0];

				  for(j = 0; j < n; j++)
                     visited_arr[j] = 0;

                  visited_arr[plist[0]] = 1;

                  // while all nodes havent been visited
                  while(all_visited != 1) {
                     for(j = 0; j < n; j++) {
                           if((weight[nextsource][j] < shortest_path) && weight[nextsource][j] != 0 && visited_arr[j] != 1) {
		                      shortest_path = j;
							  found = 1;
	                       }
					 }
					 
                     if(!found) {
                        for(j = 0; j < n; j++) {
                           if(visited_arr[j] == 0) {
                              shortest_path = j;
                              break;
						   }
						}
					 }

                     solve(2, nextsource, shortest_path, weight);
					 first_flag = 0;
					 visited_arr[shortest_path] = 1;
                     nextsource = shortest_path;
					 shortest_path = INFINITY;
					 found = 0;
					 all_visited = check_visited();
                  }
				  printf("%d ", sum);
				  for(j = 0; j <= print_count; j++) {
				     if(print_nodes[j])
					    printf("%s", print_nodes[j]);
					 if(print_weights[j])
						printf(" %d ", print_weights[j]);
				  }
				  printf("\n");
				  memset(print_nodes, '\0', sizeof(print_nodes));
				  memset(print_weights, '\0', sizeof(print_weights));
				  sum = 0;
				  print_count = 0;
				  shortest_path = INFINITY;
				  all_visited = 0;
				  first_flag = 1;
				  break;
			   case 4:
				  // Added Problem 4, avoids a given node from source to destination
				  printf("RESPONSE:\n");
                  solve(pnum, plist[0], plist[1], weight);
				  printf("\n");
				  break;
			   case 5:
                  // Added Problem 5, round trip
				  printf("RESPONSE:\n");
                  solve(pnum, plist[0], plist[1], weight);
				  printf("\n");
			      break;
               default:
				  printf("ERROR! invalid problem number!\n");
				  break;
			}
			memset(buffer, '\0', sizeof(buffer));
			memset(plist, '\0', sizeof(plist));
			i = 0;
			p = 0;

		 } else {
		    buffer[i] = tolower(input);
		    i++;
         }
      }
   }
   fclose(pfile);

return 0;
}

// Solve performs Dijkstra's Algorithm
void solve(int pnum, int source, int destin, int weight[30][30]) {
   int d, i, p, l, m, mini, udes;
   int visited[30], updated[100][100], path[100];

   for(d = 0; d < n; d++) {
     fdist[d] = INFINITY;
	 visited[d] = 0;
   }

   fdist[source] = 0;
   p = 0;
   memset(updated, '\0', sizeof(updated));

   for(i = 0; i < n; i++) {
      mini = -1;
	  for(d = 0; d < n; d++) {
	     if(!visited[d] && ((mini == -1) || (fdist[d] < fdist[mini])))
	        mini = d;
      }
	  visited[mini] = 1;

	  for(d = 0; d < n; d++) {
	     if(weight[mini][d])
		    if(fdist[mini] + weight[mini][d] < fdist[d]) {
		       fdist[d] = fdist[mini] + weight[mini][d];
			   updated[d][mini] = 1;
            }
      }
   }


   if(fdist[destin] == INFINITY) {
      printf("Error!! in problemfile, no path from %s to %s!!\n", list[source], list[destin]);
	  exit(EXIT_FAILURE);
   }

	  //keeps the path we are taking through nodes
	  udes = destin;
	  while(udes != source) {
	     for(d = 0; d < n; d++) {
		    if(updated[udes][d] == 1) {
			   udes = d;
			   path[p++] = udes;
			   break;
			}
		 }
	  }
	  //output for problem 1
	  if(pnum == 1) {
	     printf("%d", fdist[destin]);
	     for(d = p - 1; d >= 0; d--) {
		    if(d > 0)
		       printf(" %s %d", list[path[d]], weight[path[d]][path[d - 1]]);
            else
			   printf(" %s %d %s", list[path[0]], weight[path[0]][destin], list[destin]);  
	     }
	  }
	  //problem 2 & 3 requires adding sum keep track of sum and path
	  if(pnum == 2) {
		 if(path[0] == plist[0] && first_flag == 1) {
			strcpy(print_nodes[print_count], list[path[0]]);
			print_weights[print_count++] = weight[path[0]][destin];
			strcpy(print_nodes[print_count], list[destin]);
			sum += weight[path[0]][destin];
		 } else {
		    for(d = p - 1; d >= 0; d--) {
		       if(d > 0) {
				 strcpy(print_nodes[print_count], list[path[d]]);
				 print_weights[print_count++] = weight[path[d]][path[d-1]];
				 strcpy(print_nodes[print_count], list[path[d-1]]);
				 sum += weight[path[d]][path[d-1]];
			   } else {
				 print_weights[print_count++] = weight[path[0]][destin];
				 strcpy(print_nodes[print_count], list[destin]);
				 sum += weight[path[0]][destin];
			   }
            }
		 }
	  }

	  if(pnum == 4) {
         for(l = 0; l < 30; l++) {
            for(m = 0; m < 30; m++) {
			   if(m != plist[1])
                  weight_cpy[l][m] = weight[l][m];
			}
		 }

         solve(1, plist[0], plist[2], weight_cpy);
         
		 memset(weight_cpy, '\0', sizeof(weight_cpy));

	  }

      if(pnum == 5) {
	     printf("%d", fdist[destin] * 2);
		 for(d = p - 1; d >= 0; d--) {
		    if(d > 0)
		       printf(" %s %d", list[path[d]], weight[path[d]][path[d - 1]]);
			else
			   printf(" %s %d %s", list[path[0]], weight[path[0]][destin], list[destin]);
		 }
	     for(d = 0; d < p; d++) {
			if(d == 0) {
			   printf(" %d %s", weight[path[0]][destin], list[path[d]]);
			   d++;
			   }
		    if(d < p)
			   printf(" %d %s", weight[path[d]][path[d - 1]], list[path[d]]);
	     }
	  }

   memset(path, '\0', sizeof(path));
}

void menu() {

   int i = 0;

   printf("----------MENU----------\n");
   printf("NODES\n");
   for(i = 0; i <= citycount; i++) {
	  printf("%s ", list[i]);
   }
   printf("\n");
   printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
   printf("COMMANDS\n");
   printf("1: Shortest path from source to destination\n");
   printf("     Syntax: 1 source destination\n");
   printf("2: Shortest path from source to destination while visiting nodes on the way\n");
   printf("     Syntax: 2 source node node... destination\n");
   printf("3: Shortest path visitng all nodes starting from source\n");
   printf("     Syntax: 3 source\n");
   printf("4: Shortest path from source to destination avoiding middle node\n");
   printf("     Syntax: 4 source node destination\n");
   printf("5: Shortest path from source to destination and comming back to source (Round Trip)\n");
   printf("     Syntax: 5 source destination\n");
   printf("\n");
}

int check_visited() {

   int i;

   for(i = 0; i < n; i++) {
      if(visited_arr[i] == 0) {
         return 0; 
	  }
   }

   return 1;
}
