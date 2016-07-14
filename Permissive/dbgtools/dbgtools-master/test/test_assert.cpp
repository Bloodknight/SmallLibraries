#include <dbgtools/assert.h>

#include <stdio.h>

assert_action assert_callback( const char* cond, const char* msg, const char* file, unsigned int line, void* /*user_data*/ )
{
	printf("assert fail at: %s( %u ): %s -> \"%s\"\n", file, line, cond, msg);

	// ... skip all asserts ...
	return ASSERT_ACTION_NONE;
}

int main( int, char** )
{
	assert_register_callback( assert_callback, 0x0 );

	// ... standard assert ...
	ASSERT( false );

	// ... assert with message ...
	ASSERT( false, "assert with message" );

	// ... assert with message and args ...
	ASSERT( false, "assert with message %s %d", "a string", 1337 );

	// ... assert is a statement ...
	if( true )
		ASSERT( false, "is statement" );
	else
	{}

	// ... assert is also a statement that can be used with the ternary operator ...
	true ? ASSERT( false, "in ternary op" ) : ASSERT( false, "also in ternary op" );

	// ... assert should not warn for unused variable when not used ...
	int i_am_used = 1;
	ASSERT( i_am_used == 1 );

	bool verified = false;
	VERIFY( verified = true );

	if( !verified )
		printf("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO1 ( ERROR ERROR ERROR )!\n");

	verified = false;
	if( true )
		VERIFY( verified = true );

	if( !verified )
		printf("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO2 ( ERROR ERROR ERROR )!\n");

	return 0;
}
