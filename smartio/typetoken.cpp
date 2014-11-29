
#include "typetoken.hpp"

namespace typetoken
{

std::atomic<impl_token_t> impltokenbase::counter = ATOMIC_VAR_INIT(0);

}
