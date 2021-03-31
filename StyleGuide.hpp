//filenames in CamelCase
//example: LocalPlayer.cpp

//header files only *.hpp
//example: LocalPlayer.hpp

//ordinary variable
int sorttype_name;
//example:
int i_health;

//constants
const int NAME = 0;
//example:
const int LIST_SIZE = 255;

//macroses
#define NAME(var1, var2) value
//example
#define SUM(a, b) (a + b)

//global variable
int g_sorttype_name;
//example:
bool g_b_working;

//voids and functions
void name_of_void(int var1) {};
int name_of_function(int var1) {};
//example:
void set_health(int value) {};
void get_health() {};

//class
class c_name {
private:
  int _variable;

public:
  c_name() {};
};
//example:
class c_base_entity {
private:
  int base;

public:
  c_base_entity(): base(0) {};
};

//struct
struct s_name {
  int variable;
  //useless varibale
  int _padAddress16;
};
//example:
struct s_settings {
  bool enable;
  int _pad0x1;
};

//enums(only enum-class or enum-struct)
enum struct en_name: int {
  Variable0 = 0,
};
//example:
enum struct en_class_id: int {
  InvalidLast = 0,
};