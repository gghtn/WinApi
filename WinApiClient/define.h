#pragma once

// �̱��� ��ũ��
#define SINGLE(type)  public:\
							static type* GetInstance()\
							 {\
								static type mgr;\
								return &mgr;\
							 }\
					 private:\
							type();\
							~type();