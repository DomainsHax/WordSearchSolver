#include <iostream>
#include <vector>
#include <fstream>

struct Found
{
  int id;
  int line;
  int column;
  int dir; 
  int lenght;
  int same_initial_letters; 
};

int main()
{ 
  //MAP VECTOR
  std::vector<std::string> vec;
  std::ifstream M("Map.txt");

  std::string String_M;

  if(!M)
    {
      std::cout << "The file Map.txt doesn't exist" << '\n';
      return -1;
    }
  
  while(getline(M, String_M))
    {
      vec.push_back(String_M);
    }
  
  
  //SEARCH VECTOR
  std::vector<std::string> Search; 
  std::ifstream S("Search.txt");

  std::string String_S;

  if(!S)
    {
      std::cout << "The file Search.txt doesn't exist" << '\n';
      return -1;
    }

  while(getline(S, String_S)) 
    {
      Search.push_back(String_S);
    }

  //VECTOR WORDS FOUND
  std::vector<Found> vec_found;
  
  enum dir { LEFT_RIGHT, RIGHT_LEFT, UP_DOWN, DOWN_UP, DIAG_UP_LEFT, DIAG_UP_RIGHT, DIAG_DOWN_LEFT, DIAG_DOWN_RIGHT };

  int MAX_COLUMN = 0;
  
  for(int v = 0; v < vec.size(); v++)
    {
      if(vec[v].size() > MAX_COLUMN)
	{
	  MAX_COLUMN = vec[v].size();
	}
    }

  int MAX = 0;
 
  if(MAX_COLUMN < vec.size())
    { 
      MAX = vec.size();
    }else
    {
      MAX = MAX_COLUMN;
    }
  
  //SEARCH
  for(int word = 0; word < Search.size(); word++) 
    {

      bool isWord = false;

      //SAME_INITIAL_LETTERS (ANTI-BUG)
      int equal = 0;

      bool eq = false;
      
      for(int e = 0; e < Search[word].size(); e++)
	{
	  if(Search[word][0] != Search[word][e])
	    {
	      eq = true;
	    }
	  
	  if(Search[word][0] == Search[word][e] and eq == false)
	    {
	      equal++;
	    }
	}

      
      //----------HORIZONTAL----------
  
      //LEFT --> RIGHT
      if(isWord == false)
	{
	  for(int l = 0; l < vec.size(); l++)
	    {
	      int i = 0;
	      for(int c = 0; c < vec[l].size(); c++)
		{
		  if(vec[l][c] == Search[word][i])
		    {
		      if(i + 1 == Search[word].size() && isWord == false)
			{
			  i++;

			  isWord = true;
			  
			  Found found;

			  int len = Search[word].size();

			  found.id = word;
			  found.line = l;
			  found.column = c - Search[word].size() + 1;
			  found.dir = LEFT_RIGHT;
			  found.lenght = len;
			  found.same_initial_letters = equal;
		      
			  vec_found.push_back(found);
			}else
			{
			  i++;
			}
		    }else
		    {
		      i = 0;
		      
		      if(vec[l][c] == Search[word][i])
			{
			  i = 1;
			  if(vec[l][c] == vec[l][c - 1])
			    {
			      i = equal;
			    }
			}
		    }
		}
	    }
	}

      
      //RIGHT --> LEFT 
      if(isWord == false)
	{
	  for(int l = 0; l < vec.size(); l++)
	    {
	      int i = 0;
	      for(int c = vec[l].size() - 1; c >= 0; c--)
		{
		  if(vec[l][c] == Search[word][i])
		    {
		      if(i + 1 == Search[word].size() && isWord == false)
			{
			  i++;

			  isWord = true;
			  
			  Found found;

			  int len = Search[word].size();

			  found.id = word;
			  found.line = l;
			  found.column = c + Search[word].size() - 1;
			  found.dir = RIGHT_LEFT;
			  found.lenght = len;
			  found.same_initial_letters = equal;
		      
			  vec_found.push_back(found);
			}else
			{
			  i++; 
			}
		    }else
		    {
		      i = 0;
		  
		      if(vec[l][c] == Search[word][i])
			{
			  i = 1;
			  if(vec[l][c] == vec[l][c + 1])
			    {
			      i = equal;
			    }
			}
		    }
		}
	    }
	}


      //-----------VERTICAL------------
      
      //UP --> DOWN
      if(isWord == false)
	{
	  for(int c = 0; c < MAX_COLUMN; c++)
	    {
	      int i = 0;
	      for(int l = 0; l < vec.size(); l++)
		{
		  if(vec[l][c] == Search[word][i])
		    {
		      if(i + 1 == Search[word].size() && isWord == false)
			{
			  i++;

			  isWord = true;

			  Found found;

			  int len = Search[word].size();

			  found.id = word;
			  found.line = l - Search[word].size() + 1;
			  found.column = c;
			  found.dir = UP_DOWN;
			  found.lenght = len;
			  found.same_initial_letters = equal;

			  vec_found.push_back(found);
			}else
			{
			  i++; 
			}
		    }else
		    {
		      i = 0;

		      if(vec[l][c] == Search[word][i])
			{
			  i = 1;
			  if(vec[l][c] == vec[l - 1][c])
			    {
			      i = equal;
			    }
			}
		    }
		}
	    }
	}
      
      
      //DOWN --> UP
      if(isWord == false)
	{
	  for(int c = 0; c < MAX_COLUMN; c++)
	    {
	      int i = 0;
	      for(int l = vec.size() - 1; l >= 0; l--)
		{
		  if(vec[l][c] == Search[word][i])
		    {
		      if(i + 1 == Search[word].size() && isWord == false)
			{
			  i++;

			  isWord = true;

			  Found found;

			  int len = Search[word].size();

			  found.id = word;
			  found.line = l + Search[word].size() - 1;
			  found.column = c;
			  found.dir = DOWN_UP;
			  found.lenght = len;
			  found.same_initial_letters = equal;

			  vec_found.push_back(found);           
			}else
			{
			  i++; 
			}
		    }else
		    {
		      i = 0;

		      if(vec[l][c] == Search[word][i])
			{
			  i = 1;
			  if(vec[l][c] == vec[l + 1][c])
			    {
			      i = equal;
			    }
			}
		    }
		}
	    }
	}


      
      //--------DIAGONAL-COLUMN--------

      //UP_LEFT --> DOWN_RIGHT
      if(isWord == false)
	{
	  for(int l = 0; l < vec.size(); l++)
	    {
	      for(int c = 0; c < vec[l].size(); c++)
		{
		  int i = 0;
		  
		  for(int cont = 0; cont < MAX; cont++)
		    {
		      if(l + cont >= 0 && l + cont < vec.size() && c + cont >= 0 && c + cont < vec[l + cont].size())
			{
			  if(vec[l + cont][c + cont] == Search[word][i])
			    {
			      if(i + 1 == Search[word].size() && isWord == false)
				{
				  i++;

				  isWord = true;

				  Found found;

				  int len = Search[word].size();

				  found.id = word;
				  found.line = (l + cont) - Search[word].size() + 1;
				  found.column = (c + cont) - Search[word].size() + 1;
				  found.dir = DIAG_UP_LEFT;
				  found.lenght = len;
				  found.same_initial_letters = equal;

				  vec_found.push_back(found);
				}else
				{
				  i++; 
				}
			    }
			}
		    }
		}
	    }
	}


      //UP_RIGHT --> DOWN_LEFT
      if(isWord == false)
	{
	  for(int l = 0; l < vec.size(); l++)
	    {
	      for(int c = vec[l].size() - 1; c >= 0; c--)
		{
		  int i = 0;
		  
		  for(int cont = 0; cont < MAX; cont++)
		    {
		      if(l + cont >= 0 && l + cont < vec.size() && c - cont >= 0 && c - cont < vec[l + cont].size())
			{
			  if(vec[l + cont][c - cont] == Search[word][i])
			    {
			      if(i + 1 == Search[word].size() && isWord == false)
				{
				  i++;

				  isWord = true;

				  Found found;

				  int len = Search[word].size();

				  found.id = word;
				  found.line = (l + cont) - Search[word].size() + 1;
				  found.column = (c - cont) + Search[word].size() - 1;
				  found.dir = DIAG_UP_RIGHT;
				  found.lenght = len;
				  found.same_initial_letters = equal;

				  vec_found.push_back(found);
				}else
				{
				  i++; 
				}
			    }
			}
		    }
		}
	    }
	}


      //DOWN_LEFT --> UP_RIGHT
      if(isWord == false)
	{
	  for(int c = 0; c < MAX_COLUMN; c++)
	    {
	      for(int l = vec.size() - 1; l >= 0; l--)
		{
		  int i = 0;
		  
		  for(int cont = 0; cont < MAX; cont++)
		    {
		      if(l - cont >= 0 && l - cont < vec.size() && c + cont >= 0 && c + cont < vec[l - cont].size())
			{
			  if(vec[l - cont][c + cont] == Search[word][i])
			    {
			      if(i + 1 == Search[word].size() && isWord == false)
				{
				  i++;

				  isWord = true;

				  Found found;

				  int len = Search[word].size();

				  found.id = word;
				  found.line = (l - cont) + Search[word].size() - 1;
				  found.column = (c + cont) - Search[word].size() + 1;
				  found.dir = DIAG_DOWN_LEFT;
				  found.lenght = len;
				  found.same_initial_letters = equal;

				  vec_found.push_back(found);
				}else
				{
				  i++; 
				}
			    }
			}
		    }
		}
	    }
	}

      
      //DOWN_RIGHT --> UP_LEFT
      if(isWord == false)
	{
	  for(int c = MAX_COLUMN - 1; c >= 0; c--)
	    {
	      for(int l = vec.size() - 1; l >= 0; l--)
		{
		  int i = 0;
		  
		  for(int cont = 0; cont < MAX; cont++)
		    {
		      if(l - cont >= 0 && l - cont < vec.size() && c - cont >= 0 && c - cont < vec[l - cont].size())
			{
			  if(vec[l - cont][c - cont] == Search[word][i])
			    {
			      if(i + 1 == Search[word].size() && isWord == false)
				{
				  i++;
				  isWord = true;

				  Found found;

				  int len = Search[word].size();

				  found.id = word;
				  found.line = (l - cont) + Search[word].size() - 1;
				  found.column = (c - cont) + Search[word].size() - 1;
				  found.dir = DIAG_DOWN_RIGHT;
				  found.lenght = len;
				  found.same_initial_letters = equal;

				  vec_found.push_back(found);             
				}else
				{
				  i++; 
				}
			    }
			}
		    }
		}
	    }
	}
    }

  std::cout << "START MAP: " << '\n' << '\n';
  //START MAP
  for(int v = 0; v < vec.size(); v++)
    {
      std::cout << vec[v] << '\n';
    }

  //BARRAGE OF THE FIND WORDS

  for(int n = 0; n < vec_found.size(); n++)
    {
      //LEFT_RIGHT
      if(vec_found[n].dir == LEFT_RIGHT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line][vec_found[n].column + i] = '-';
	    }
	}

      //RIGHT_LEFT
      if(vec_found[n].dir == RIGHT_LEFT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line][vec_found[n].column - i] = '-';
	    }
	}

      //UP_DOWN
      if(vec_found[n].dir == UP_DOWN)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line + i][vec_found[n].column] = '-';
	    }
	}

      //DOWN_UP
      if(vec_found[n].dir == DOWN_UP)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line - i][vec_found[n].column] = '-';
	    }
	}

     //DIAG_UP_LEFT
      if(vec_found[n].dir == DIAG_UP_LEFT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line + i][vec_found[n].column + i] = '-';
	    }
	}

      //DIAG_UP_RIGHT
      if(vec_found[n].dir == DIAG_UP_RIGHT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line + i][vec_found[n].column - i] = '-';
	    }
	}

      //DIAG_DOWN_LEFT
      if(vec_found[n].dir == DIAG_DOWN_LEFT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line - i][vec_found[n].column + i] = '-';
	    }
	}

      //DIAG_DOWN_RIGHT
      if(vec_found[n].dir == DIAG_DOWN_RIGHT)
	{
	  for(int i = 0; i < vec_found[n].lenght; i++)
	    {
	      vec[vec_found[n].line - i][vec_found[n].column - i] = '-';
	    }
	}
    }


  std::cout << '\n' << '\n' << "BARRAGE OF THE FIND WORDS: " << '\n' << '\n';
  //FINAL MAP
  for(int v = 0; v < vec.size(); v++)
    {
      std::cout << vec[v] << '\n';
    }

  
  std::cout << '\n' << '\n' << "RESULT: " << '\n' << '\n';
  
  //FINAL WORD/PHRASE
  for(int l = 0; l < vec.size(); l++)
    {
      for(int c = 0; c < vec[l].size(); c++)
	{
	  if(vec[l][c] != '-')
	    {
	      std::cout << vec[l][c];
	    }
	}
    }

  std::cout << '\n';
  
  return 0;
}

