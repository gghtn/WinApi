#pragma once

// ΩÃ±€≈Ê ∏≈≈©∑Œ
#define SINGLE(type) static type* GetInstance()\
					 {\
						static type mgr;\
						return &mgr;\
					 }