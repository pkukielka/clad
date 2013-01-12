namespace * clang.thrift

/**
 *	Mappings:
 *		
 *      int             ->      i32
 *      unsigned        ->      u32
 *      unsigned long   ->      u64
 *      time_t          ->      t64
 */

typedef i32 int

typedef i32 u32

typedef i64 u64

typedef i64 t64

 /**
 * \brief Unique identifier for any dynamically allocated resource.
 *  It replaces void* pointers in the Thrift API.
 */
typedef i64 ResourceId
