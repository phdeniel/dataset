#include "dataset_api.h"

int dataset_new(char *dsname)
{
	return 0;
};

int dataset_manifest_dump(struct dataset *ds,
			  int fd)
{
	return 0;
}

int dataset_manifest_restore(const char *dsname,
			     int fd)
{
	return 0;
}

int dataset_getmd(const char *dsname,
		  dataset_md_t md)
{
	return 0;
}

int dataset_setmd(const char *dsname,
		  dataset_md_t md, int mask)
{
	return 0;
}

int dataset_delete(const char *dsname)
{
	return 0;
}

int dataset_session_acquire(const char *dsname,
			    dataset_access_t access_type,
			    dataset_session_t session)
{
	return 0;
}
int dataset_session_add_object(dataset_session_t session,
			       char *object_uri)
{
	return 0;
}

int dataset_session_remove_object(dataset_session_t session,
				  char *object_uri)
{
	return 0;
}

int dataset_session_access_object(dataset_session_t session,
				  const char *object_uri,
				  dataset_access_t flags)
{
	return 0;
}

int dataset_session_commit(dataset_session_t *session, bool release)
{
	return 0;
}

