#include <iostream>
#include <cassert>
#include <cctype>
#include <string>
using namespace std;

bool hasCorrectSyntax(string);

bool isTranslateable(string);

bool problem2(string);

int findBadBeat2(string);

bool problem3(string);

int findBadBeat3(string);

int translateSong(string, string&, int&);

int badBeatFinder(string);

int main()
{
	string s = "";
	string instrs = "smh";
	int badb = -999;
	cout << "Write song: ";
	getline(cin, s);
	cout << "Translate: " << translateSong(s, instrs, badb) << endl;
	cout << "badb: " << badb << endl;
}


bool hasCorrectSyntax(string song)
{
	for (int c = 0; c != song.size(); c++) //goes through series of checks to see if entered song is syntacically correct
	{
		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					if ((song[c + 3] == '/'))
					{
						c = c + 3; // move on past the slash
						continue;
					}

					else
					{
						return false;
					}
				}

				else if ((song[c + 2] == '/'))
				{
					c = c + 2; // move on past the slash
					continue;
				}

				else
				{
					return false;
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				c++; // move on past the slash
				continue;
			}
			else
			{
				return false;
			}

		}

		else if (song[c] == '/') //is there a pause here?
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool isTranslateable(string song)
{
	for (int c = 0; c != song.size(); c++) //goes through series of checks to see if entered song is syntacically correct
	{


		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (i - 3);
				}

				else if (numBeat == 1)
				{
					return false;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (i - 2);
				}

				else
				{
					return false;
				}
			}
			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				c++;
				continue;
			}
			else
			{
				return false;
			}
		}

		else if (song[c] == '/') //is there a pause here?
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool problem2(string song)
{
	for (int c = 0; c != song.size(); c++)
		//goes through series of checks to see 
		//if entered song does not have 1s or 0s
	{

		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}



				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					
					if (numBeat == 0 || numBeat == 1)
					{
						return false;
					}

					int i = 3;

					c = c + (i - 3);
				}

				else if (numBeat == 1 || numBeat == 0)
				{
					return false;
				}
			}

		}
	}
	return true;
}

int findBadBeat2(string song) // finds the bad beat for problem 2
{
	int beats = 1, start = 0;


	for (int c = 0; c != song.size(); c++)
		//goes through series of checks to see 
		//if entered song holds sustained beats correctly
	{
		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}



				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					if (numBeat == 0 || numBeat == 1)
					{
						return beats;
					}

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							beats++;
							continue;
						}
						else
						{
							return beats;
						}
					}
					c = c + numBeat;
				}

				else if (numBeat == 1 || numBeat == 0)
				{
					return beats;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							beats++;
							continue;
						}
						else
						{
							return beats;
						}
					}
					c = c + numBeat;
				}
			}

		}

		else
		{
			if (c != 0)
			{
				beats++;
			}
		}
	}
}

bool problem3(string song)
{
	for (int c = 0; c != song.size(); c++)
		//goes through series of checks to see 
		//if entered song holds sustained beats correctly
	{

		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (i - 3);
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							continue;
						}
						else
						{
							return false;
						}
					}
					c = c + (i - 2);
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				c++;
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

int findBadBeat3(string song) //finds the bad beat for problem 3
{ //needs work 
	int beats = 1, start = 0;
	for (int c = 0; c != song.size(); c++)
		//goes through series of checks to see 
		//if entered song holds sustained beats correctly
	{

		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							
							beats++;
							continue;
						}
						else
						{
							beats++;
							return beats;
						}
					}
					c = c + numBeat;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							beats++;
							continue;
						}
						else
						{
							beats++;
							return beats;
						}
					}
					c = c + numBeat;
				}
			}

			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				c++;
				continue;
			}
			else
			{
				beats = beats + (c);
				return beats;
			}
		}
	}
}

int badBeatFinder(string song)
{
	//goes through series of checks 
	// to see if entered song has badBeats
	int beats = 1, start = 0;
	for (int c = 0; c != song.size(); c++)
	{

		if (song[c] == 'g' || song[c] == 'r' || song[c] == 'y' || song[c] == 'b'
			|| song[c] == 'o' || song[c] == 'G' || song[c] == 'R'
			|| song[c] == 'Y' || song[c] == 'B' || song[c] == 'O')
		{

			if (isdigit(song[c + 1]))
			{// is the song following proper sustain note syntax?

				int numBeat = song[c + 1];


				for (int k = 48; k < 57; k++)
				{
					if (k == numBeat)
					{
						numBeat = k - 48;
						break;
					}
				}


				if (isdigit(song[c + 2]))
				{ // check for proper two digit procedure

					numBeat = numBeat * 10;

					int numBeat1 = song[c + 2];


					for (int k = 48; k < 57; k++)
					{
						if (k == numBeat1)
						{
							numBeat1 = k - 48;
							break;
						}
					}

					numBeat = numBeat + numBeat1;

					if (numBeat <= 1)
					{
						return beats;
					}

					int i = 3;
					for (; i - 3 < numBeat; i++)
					{

						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							beats++;
							continue;
						}
						else
						{
							beats++;
							return beats;
						}
					}
					c = c + numBeat + 1;
				}

				else if (numBeat <= 1)
				{
					return beats;
				}

				else if ((song[c + 2] == '/'))
				{
					int i = 2;
					for (; i - 2 < numBeat; i++)
					{
						if (song[c + i] == '/') // does song have the right # of slashes for sustain
						{
							if (start == 0)
							{
								start++;
								continue;
							}
							beats++;
							continue;
						}
						else
						{
							beats++;
							return beats;
						}
					}
					c = c + (numBeat + 1);
				}

				else
				{
					return beats;
				}
			}
			else if (song[c + 1] == '/') // is the song following normal note procedure?
			{
				if (start == 0)
				{
					start++;
					continue;
				}
				beats++;
				continue;
			}
			else
			{
				return beats;
			}
		}

		else if (song[c] == '/') //is there a pause here?
		{
			cout << "pause" << endl;
			if (start == 0)
			{
				start++;
				continue;
			}
			beats++;
			continue;
		}
		else
		{
			return beats;
		}
	}
	return 0;
}

int translateSong(string song, string& instructions, int& badBeat)
{
	if (!hasCorrectSyntax(song))
	{
		return 1;
	}

	if (!problem2(song))
	{
		badBeat = findBadBeat2(song);
		return 2;
	}
	if (!problem3(song))
	{
		badBeat = findBadBeat3(song);
		cout << "BadBeat: " << badBeat << endl;
		return 3;
	}

	if (isTranslateable(song))
	{
		// insert translate function
		return 0;
	}
}