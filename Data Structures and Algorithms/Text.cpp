/*
	private:
		const char* text;
		int sz;  //length of string not including null terminator
	public:
		String (const char* char_array);
		~String ();
		void displayString ();  //active
		int length ();
		const char* getText ();
		int a_to_i ();
		float f_to_i();
		String* i_to_a (int number);
		String* f_to_a (float number);
		
		int find (char delimiter, int start);
*/

String::String(const char* char_array)
{
	sz = strlen (char_array);
	char* text = new char[sz+1];
	for (int i = 0; i < sz; i++)
	{
		text[i] = char_array[i];
	}
	text[sz] = 0;
	this->text = (const char*)text //tells the computer that you're using the the text you just created in the line before
}

int String::length()
{
	return sz;
}

const char* String::getText()
{
	return text;
}

void String::displayString()
{
	cout << text;
}

String::~String()
{
	delete[] text;
}