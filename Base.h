enum color{RED,BLUE,WHITE,BLACK};
enum direction{UP,DOWN,LEFT,RIGHT,NONE};

class point{
	public: 
	color _color;
	point(){
		_color = WHITE;
	}
	void assign(bool _change){
		if(_change){
			_color = WHITE;
		}
	}
};

class segment{
	public: 
	bool isHead;
	int posx, posy;
	direction _cache;
	segment* next;
	segment* previous;
	segment(int a, int b, bool head,segment* previous,segment* next,direction cache)
	{
		posx = a;
		previous = previous;
		next = next;
		_cache = cache;
		posy = b;
		isHead = head;
	}
	segment(){
	isHead = false;
	_cache = UP;
	posx = posy = 25;	
	}
};


