#include "IHanaService.h"

namespace android {

	class HanaService :
		public BnHanaService
	{
		public:
			void hanaTouch(uint32_t, uint32_t);
	};

}; // namespace android

