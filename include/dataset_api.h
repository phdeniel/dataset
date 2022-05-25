#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ALTGROUPS 100

struct dataset_md {
	char *name;
	char *URI;
	uid_t owner;
	gid_t gowner;
	gid_t altgroups[MAX_ALTGROUPS];
	time_t creation;
	time_t last_allocation;
	time_t last_commit;
};

typedef struct dataset_md dataset_md_t;

enum dataset_md_mask {
	NOTHING =	0x0000,
	NAME = 		0x0001,	
	URI = 		0x0002,
	OWNER = 	0x0004,
	GOWNER = 	0x0008,
	ALTGROUPS = 	0x0010,
	CREATION_TIME = 0x0011,
	ALLOCATION_TIME=0x0012,
	COMMIT_TIME =	0x0014,
}; 
typedef enum dataset_md_mask dataset_md_mask_t;

typedef char *  dataset_session_t;

struct dataset {
	int nothing;
};
typedef struct dataset dataset_t;

enum data_access {
	READ = 	0x01,
	WRITE =	0x02,
	RW =	0x03, /* READ|WRITE */
};
typedef enum data_access dataset_access_t;

int dataset_init(const char *configfile);
int dataset_shutdown(void);

int dataset_new(char *dsname);
int dataset_manifest_dump(struct dataset *ds,
			  int fd);
int dataset_manifest_restore(const char *dsname,
			     int fd);
int dataset_getmd(const char *dsname,
		  dataset_md_t md);
int dataset_setmd(const char *dsname,
		  dataset_md_t md, int mask);
int dataset_delete(const char *dsname);

int dataset_session_acquire(const char *dsname,
			    dataset_access_t access_type,
			    dataset_session_t session);
int dataset_session_add_object(dataset_session_t session,
			       char *object_uri);
int dataset_session_remove_object(dataset_session_t session,
				  char *object_uri);
int dataset_session_access_object(dataset_session_t session,
				  const char *object_uri,
				  dataset_access_t flags);
int dataset_session_commit(dataset_session_t *session, bool release);
