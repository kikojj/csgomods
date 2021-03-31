#pragma once
#include <Windows.h>

class c_recv_prop;

class c_recv_table
{
public:

	c_recv_prop*	p_props;
	int						i_props;
	void*					decoder;
	char*					net_table__name;
	bool					initialized;
	bool					in_main_list;
};

//unnecessary class pointers have been converted to void* for simplicity

class c_recv_prop{
public:
	char*					var_name;
	void*					recv_type;
	int						flags;
	int						string_buffer_size;
	int						inside_array;
	const void*		extra_data;
	c_recv_prop*	array_prop;
	void*					array_length_proxy;
	void*					proxy_fn;
	void*					data_table_proxy_fn;
	c_recv_table*	data_table;
	int           offset;
	int           element_stride;
	int           elements;
	const char*		parent_array_prop_name;
};

class c_client_class
{
public:
	void*						create_fn;
	void*						create_event_fn;
	char*						network_name;
	c_recv_table*		recv_table;
	c_client_class*	next;
	int							class_id;
};