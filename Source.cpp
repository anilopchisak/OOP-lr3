#include <iostream>
using namespace std;

class BaseObject
{
public:
	BaseObject()
	{
		printf("BaseObject() - default constuctor\n");
	}
	virtual ~BaseObject()
	{
		printf("~BaseObject() - destructor\n");
	}
};
class Figure : public BaseObject
{
protected:
	int corner;
	int side;
public:
	Figure()
	{
		printf("Figure() - default constructor\n");
		corner = 0;
		side = 0;
	}
	Figure(int corner, int side)
	{
		printf("Figure(int corner, int side) - constructor with parameters\n");
		this->corner = corner;
		this->side = side;
	}
	Figure(const Figure& f) //переносит все свойства из того объекта, который передали
	{
		printf("Figure(const Figure& f) - copy constructor\n");
		corner = f.corner;
		side = f.side;
	}
	virtual ~Figure()
	{
		//printf("%d, %d\n", corner, side); //вывод текущего состояния объекта
		printf("~Figure - destructor\n");
	}
};
class Storage
{
private:
	BaseObject** _objects; //создание массива объектов
	int _count; //количество объектов в массиве
	int _size; //размер массива
public:
	Storage(int size) //constructor with parameters
	{
		printf("Storage(int count) - constructor\n");
		_size = size;
		_count = size;
		_objects = new BaseObject * [_size];
		for (int i = 0; i < _size; i++) _objects[i] = nullptr;
	}
	virtual ~Storage()
	{
		printf("~Storage(int count) - destructor\n");
		for (int i = 0; i < _size; i++)
			if (_objects[i] != nullptr) delete _objects[i]; //удаляем каждый элемент массива
		delete _objects; //удаляем массив
	}

	virtual void setObject(int index, BaseObject* object)
	{
		printf("setObject(int index, BaseObject* object)\n");
		_objects[index] = object;
	}
	//virtual void addObject2() //add object to the first empty cell
	//{
	//	printf("addObject()\n");
	//	_count = _count + 1;
	//	if (_size < _count)
	//	{
	//		createNewArray();
	//		addObject2();
	//	}
	//	else 
	//	{
	//		for (int i = 0; i < _size; i++)
	//			if (_objects[i] == nullptr)
	//			{
	//				setObject(i, new Figure);
	//				//printf("%d\n", i);
	//				break;
	//			}
	//	}
	//	
	//}

	virtual int getCount()
	{
		printf("getCount()\n");
		return _size;
	}
	BaseObject getObject(int index)
	{
		printf("getObject(int i)\n");
		return *_objects[index];
	}
	virtual void createNewArray()
	{
		BaseObject** _objects2 = new BaseObject * [_size + 50];
		for (int i = 0; i < (_size + 50); i++) _objects2[i] = nullptr;
		for (int i = 0; i < _size; i++) _objects2[i] = _objects[i];
		this->_size = _size + 50;
		delete _objects;
		_objects = _objects2;
	}
	virtual void addObject(int index, BaseObject* b)
	{
		printf("addObject()\n");
		if (_objects[index] != nullptr) return;
		_count = _count + 1;
		if (_size < _count)
		{
			createNewArray();
			addObject(index, new BaseObject);
		}
		else if (_objects[index] == nullptr) setObject(index, b);
	}
	virtual void deleteObject(int index)
	{
		printf("deleteObject(int i)\n");
		if (_objects[index] != nullptr)
		{
			_count = _count - 1;
			delete _objects[index];
			_objects[index] = nullptr;
		}
	}
};

void make_storage(int n)
{
	int command = 0;
	{
		Storage storage(n); // создаем хранилище
		for (int i = 0; i < storage.getCount(); i++) storage.setObject(i, new Figure); // добавляем в него объекты
		printf("\n\n");

		//обращаемся поочередно ко всем
		for (int i = 0; i < storage.getCount(); i++)
		{
			command = rand() % 4;
			n = storage.getCount();
			int index = rand() % n; printf("%d\n", index);
			switch (command)
			{
			case 0:
				storage.addObject(index, new BaseObject);
				break;
			case 1:
				storage.deleteObject(index);
				break;
			case 2:
				storage.getCount();
				break;
			case 3:
				storage.getObject(index);
				break;
			}
			printf("\n");
		}
	}
}
void clear_system()
{
	system("pause");
	system("cls");
}

int main()
{
	srand(time(NULL));

	make_storage(10);
	clear_system();

	make_storage(100);
	clear_system();

	make_storage(1000);
	clear_system();

	make_storage(10000);
	clear_system();

	return 0;
}