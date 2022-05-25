#include <stdio.h>
#include <sys/param.h>
#include <string.h>
#include <errno.h>

#include "dataset_api.h"
#include "git2.h"

/*
 * Internam Types
 */

struct dataset_session_git2 {
	char remote[MAXPATHLEN];
	char local[MAXPATHLEN];
	git_repository *repo;
};
typedef struct dataset_session_git2 dataset_session_git2_t;

/*
 * Internal variables
 */
git_repository *repo = NULL;
const char git_remote_dir[] = "/tmp/BASE";
const char session_dir[] = "/tmp/DS";

/* 
 * Internal functions
 */

static void  print_git_error(int error)
{
  const git_error *e = git_error_last();
  printf("Error %d/%d: %s\n", error, e->klass, e->message);
}


/*
 * Functions exposed to the end user 
 */

int dataset_init(const char *configfile)
{
	/* Init the libgit2 API */
	git_libgit2_init();

	return 0;
}

int dataset_shutdown(void)
{
	if (repo)
		git_repository_free(repo);

	git_libgit2_shutdown();
	return 0;
}

int dataset_new(char *dsname)
{
#if 0
	int rc = 0;
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
	char repopath[MAXPATHLEN];

	snprintf(repopath, MAXPATHLEN, "%s/%s", git_remote_dir, dsname);
	opts.flags |= GIT_REPOSITORY_INIT_MKPATH;
	opts.description = "My Dataset Repository";

	rc = git_repository_init_ext(&repo, repopath, &opts);
	if (rc) {
		print_git_error(rc);
		return rc;
	}
#endif
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
	int rc = 0;
	git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	dataset_session_git2_t *session_git2;

	session = (char *)malloc(sizeof(dataset_session_git2_t));
	if (!session)
		return ENOMEM;
	session_git2 = (dataset_session_git2_t *)session;

	snprintf(session_git2->remote, MAXPATHLEN, "%s/.git", git_remote_dir); 
	snprintf(session_git2->local, MAXPATHLEN, "%s/%s", session_dir, dsname);

	rc = git_clone(&session_git2->repo,
		       session_git2->remote,
		       session_git2->local,
		       &clone_opts);
	if (rc) {
		print_git_error(rc);
		return rc;
	}

	rc = git_checkout_head(session_git2->repo, NULL);
	if (rc) {
		print_git_error(rc);
		return rc;
	}

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

int main(int argc, char *argv[])
{
	return 0;
}
