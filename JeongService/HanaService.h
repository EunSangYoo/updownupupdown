#include "IHanaService.h"

namespace android {

	class HanaService :
		public BnHanaService
	{
		public:
			int lock_check(void);
			int touch_check(void);
	};

}; // namespace android
