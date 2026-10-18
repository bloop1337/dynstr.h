#ifndef DYNSTR
#define DYNSTR

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/param.h>

#ifndef DYNSTR_FORMAT
#define DYNSTR_FORMAT "%*s"
#endif // DYNSTR_FORMAT

typedef struct {
	char* data;
	size_t length;
	size_t capacity;
} Dynamic_String;

void dynstr_create(Dynamic_String* str, const char* c_str);
void dynstr_create_len(Dynamic_String* str, size_t capacity);

void dynstr_reserve(Dynamic_String* str, size_t size);
void dynstr_append(Dynamic_String* str, const char c);

bool dynstr_starts_with(Dynamic_String* str, const char* req);
bool dynstr_ends_with(Dynamic_String* str, const char* req);

void dynstr_delete(Dynamic_String *dyn_str);

#ifdef DYNSTR_IMPLEMENTATION
	void dynstr_create_len(Dynamic_String* str, size_t capacity) {	
		str->capacity = MAX(capacity, 1);
		str->length   = 0;	
		str->data     = malloc(str->capacity);
	}

	void dynstr_create(Dynamic_String* str, const char* c_str) {
		str->capacity = MAX(strlen(c_str), 1);
		str->length   = strlen(c_str);	
		str->data     = malloc(str->capacity);

		for (size_t i = 0; i < str->length; ++i) str->data[i] = c_str[i]; 
	}

	void dynstr_reserve(Dynamic_String* str, size_t size) {
		if (str == NULL || str->data == NULL) {
			dynstr_create_len(str, size);
			return;
		}

		str->data = realloc(str->data, str->capacity+size);
		str->capacity += size;
	}

	void dynstr_append(Dynamic_String* str, const char c) {
		if (str == NULL || str->data == NULL) return;
		if (str->capacity <= str->length) dynstr_reserve(str, str->capacity);

		str->data[str->length] = c;
		str->length += 1;
	}

	void dynstr_delete(Dynamic_String *dyn_str) {
		if (dyn_str == NULL || dyn_str->data == NULL) return;
		free(dyn_str->data);
		dyn_str->length   = 0;
		dyn_str->capacity = 0;
		dyn_str->data     = NULL;
	}

	bool dynstr_starts_with(Dynamic_String* str, const char* req) {
		if (str == NULL) return false;
		const size_t req_sz = strlen(req);
		if (req_sz > str->length) return false;
		
		for (size_t i = 0; i < req_sz; ++i) {
			if (req[i] != str->data[i]) return false;
		}

		return true;
	}

	bool dynstr_ends_with(Dynamic_String* str, const char* req) {
		if (str == NULL) return false;
		const size_t req_sz = strlen(req);
		if (req_sz > str->length) return false;
		
		for (size_t i = 0; i < req_sz; ++i) {
			if (req[req_sz-i] != str->data[str->length-i]) return false;
		}

		return true;
	}

#endif // DYNSTR_IMPLEMENTATION

#endif // DYNSTR
