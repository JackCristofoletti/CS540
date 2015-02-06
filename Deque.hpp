#ifndef DEQUE_H
#define DEQUE_H
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define INITIAL_CAPACITY 20

	
#define Deque_DEFINE(t)																\
	struct Deque_##t##_Iterator;													\
	struct Deque_##t{																\
		int sizeCounter;															\
		int head;																	\
		int tail;																	\
		int capacity ;																\
		t *data		;																\
		bool (*Comparison)( const t &a ,const t &b);								\
		bool (*empty)(Deque_##t *it);												\
		t &(*front)(Deque_##t *it);													\
		t &(*back)(Deque_##t *it);													\
		char type_name[6+strlen(#t)+1];															\
		void (*push_back)(Deque_##t *it , t element); 								\
		void (*push_front)(Deque_##t *it , t element);								\
		void (*double_capacity)(Deque_##t *it );									\
		void (*pop_front)(Deque_##t *it);											\
		void (*pop_back)(Deque_##t *it );											\
		void (*clear)(Deque_##t *it);												\
		int  (*size)(Deque_##t *it);												\
		Deque_##t##_Iterator  (*begin)(Deque_##t *it);								\
		Deque_##t##_Iterator  (*end)(Deque_##t *it);								\
		t &(*at)(Deque_##t *, int i);												\
		void (*dtor)(Deque_##t *it);												\
	};																				\
																					\
	struct Deque_##t##_Iterator{													\
			int current;															\
			Deque_##t *dp;															\
			void (*inc)(Deque_##t##_Iterator *it);									\
			void (*dec)(Deque_##t##_Iterator *it);									\
			t  & (*deref)(Deque_##t##_Iterator *it);								\
	};																				\
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it){						\
		it->current=(it->current+1) % (it->dp->capacity);																\
	}																				\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it){						\
		it->current=(it->current+it->dp->capacity-1) % (it->dp->capacity);						\
	}																				\
	t & Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it1){						\
		return it1->dp->data[it1->current];											\
	}																				\
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *dp){							\
		Deque_##t##_Iterator it;													\
		it.current=dp->head;														\
		it.dp = dp;																	\
		it.inc = &Deque_##t##_Iterator_inc;											\
		it.dec= & Deque_##t##_Iterator_dec;											\
		it.deref= & Deque_##t##_Iterator_deref;										\
		return it;																	\
	}																				\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t *dp){							\
		Deque_##t##_Iterator it;													\
		it.current=dp->tail;														\
		it.dp = dp;																	\
		it.inc = &Deque_##t##_Iterator_inc;											\
		it.dec=  &Deque_##t##_Iterator_dec;											\
		it.deref= & Deque_##t##_Iterator_deref;										\
		return it;																		\
	}																				\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){	\
		return it1.current == it2.current; 											\
	}																				\
																					\
	void Deque_##t##_clear(Deque_##t *dp){											\
		dp->head=0;																	\
		dp->tail=0;																	\
		dp->sizeCounter=0;															\
	}																				\
	bool Deque_##t##_equal(Deque_##t a , Deque_##t b){								\
		if(a.sizeCounter != b.sizeCounter){											\
			return false;}															\
		else{																		\
			int i;																						\
			for( i= 0 ; i < a.sizeCounter ; i++){														\
				int aloc=(a.head+i) % (a.capacity);														\
				int bloc=(b.head+i) % (b.capacity);														\
				if( a.Comparison(a.data[aloc], b.data[bloc]) || b.Comparison(b.data[bloc], a.data[aloc]))\
					return false;														\
			}																			\
		return true;																	\
		}																			\
	}																				\
	t & Deque_##t##_front(Deque_##t *dp){											\
		return dp->data[(dp->head)];												\
	}																				\
	t & Deque_##t##_back(Deque_##t *dp){	 										\
		return dp->data[(dp->tail-1) % (dp->capacity)];								\
	}																				\
	t & Deque_##t##_at(Deque_##t *dp, int i){	 									\
		return dp->data[i];															\
	}																				\
	void double_capacity(Deque_##t *dp){											\
		t *new_data;																\
		new_data=(t*) malloc(sizeof(t)*2*dp->capacity);								\
		for(int i=0; i < dp->capacity; i++){										\
			int loc=(dp->head+i) % (dp->capacity);									\
			new_data[i]=dp->data[loc] ;	}											\
		free(dp->data);																\
		dp->data=new_data;															\
		dp->head=0;																	\
		dp->tail=dp->capacity;														\
		dp->capacity=2*dp->capacity;												\
	}																				\
	void Deque_##t##_push_front(Deque_##t *dp, t element){							\
		dp->head = (dp->head - 1) & (dp->capacity-1) ;								\
		dp->data[dp->head] = element ;												\
		if(dp->head == dp->tail)													\
			double_capacity(dp);													\
		dp->sizeCounter++;															\
	}																				\
	void Deque_##t##_push_back(Deque_##t *dp, t element){							\
		dp->data[dp->tail] = element;												\
		dp->tail=(dp->tail+1) & (dp->capacity-1);									\
		if(dp->tail==dp->head)														\
			double_capacity(dp);													\
		dp->sizeCounter++;															\
	}																				\
	void Deque_##t##_pop_front(Deque_##t *dp){										\
		if(dp->sizeCounter > 0 ){													\
			dp->head = (dp->head +1) & (dp->capacity -1 );							\
			dp->sizeCounter -- ;													\
		}																			\
	}																				\
	void Deque_##t##_pop_back(Deque_##t *dp){										\
		if(dp->sizeCounter > 0 ){													\
			dp->tail = (dp->tail - 1) & (dp->capacity - 1);							\
			dp->sizeCounter=dp->sizeCounter - 1;									\
		}																			\
	}																				\
	int Deque_##t##_size(Deque_##t *dp){											\
		return dp->sizeCounter;														\
	}																				\
	void Deque_##t##_dtor(Deque_##t *dp){											\
		free(dp->data);																\
	}																				\
	bool Deque_##t##_empty(Deque_##t *dp){											\
		return dp->sizeCounter==0;													\
	}																				\
	void Deque_##t##_ctor(Deque_##t *dp, bool (*Comp)(const t& a , const t& b)){	\
		dp->head=dp->sizeCounter=dp->tail=dp->sizeCounter=0;						\
		dp->capacity=INITIAL_CAPACITY;												\
		dp->data = (t*) malloc(sizeof(t) * dp->capacity);							\
		dp->Comparison=Comp;														\
		dp->front =  &Deque_##t##_front;											\
		dp->back =  &Deque_##t##_back;												\
		dp->push_front =  &Deque_##t##_push_front;									\
		dp->push_back =  &Deque_##t##_push_back;									\
		dp->pop_front =  &Deque_##t##_pop_front;									\
		dp->pop_back =  &Deque_##t##_pop_back;										\
		dp->size =		&Deque_##t##_size;											\
		dp->clear =     &Deque_##t##_clear;											\
		dp->at=			&Deque_##t##_at;											\
		dp->dtor =      &Deque_##t##_dtor;											\
		dp->begin = &Deque_##t##_begin;												\
		dp->end =   &Deque_##t##_end;												\
		dp->empty=  &Deque_##t##_empty;												\
		strcpy(dp->type_name,"Deque_");												\
		strcat(dp->type_name,#t);													\
	}																											
	
#endif												
