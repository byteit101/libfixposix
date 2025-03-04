/*******************************************************************************/
/* Permission is hereby granted, free of charge, to any person or organization */
/* obtaining a copy of the software and accompanying documentation covered by  */
/* this license (the "Software") to use, reproduce, display, distribute,       */
/* execute, and transmit the Software, and to prepare derivative works of the  */
/* Software, and to permit third-parties to whom the Software is furnished to  */
/* do so, all subject to the following:                                        */
/*                                                                             */
/* The copyright notices in the Software and this entire statement, including  */
/* the above license grant, this restriction and the following disclaimer,     */
/* must be included in all copies of the Software, in whole or in part, and    */
/* all derivative works of the Software, unless such copies or derivative      */
/* works are solely in the form of machine-executable object code generated by */
/* a source language processor.                                                */
/*                                                                             */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    */
/* FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT   */
/* SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE   */
/* FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER */
/* DEALINGS IN THE SOFTWARE.                                                   */
/*******************************************************************************/

#if !defined(_LFP_SPAWN_H_)
# define _LFP_SPAWN_H_

#include <lfp/aux.h>

LFP_BEGIN_DECLS

#include <lfp/fcntl.h>
#include <lfp/signal.h>

#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>

typedef struct {
    uint initialized;
    uint allocated;
    struct lfp_spawn_action *actions;
    bool keep_descriptors;
    int *kfd;
    int kfd_size;
} lfp_spawn_file_actions_t;

int lfp_spawn_file_actions_init(lfp_spawn_file_actions_t *file_actions);

int lfp_spawn_file_actions_destroy(lfp_spawn_file_actions_t *file_actions);

int lfp_spawn_file_actions_addopen(lfp_spawn_file_actions_t *file_actions,
                                   int fd, const char *path,
                                   uint64_t oflags, mode_t mode);

int lfp_spawn_file_actions_addclose(lfp_spawn_file_actions_t *file_actions,
                                    int fd);

int lfp_spawn_file_actions_adddup2(lfp_spawn_file_actions_t *file_actions,
                                   int fd, int newfd);

int lfp_spawn_file_actions_addkeep(lfp_spawn_file_actions_t *file_actions,
                                   int fd);

typedef struct {
    int resource;
    struct rlimit rlim;
} lfp_rlimit_t;

typedef struct {
    uint32_t      flags;
    sigset_t      sigdefault;
    sigset_t      sigmask;
    pid_t         pgroup;
    uid_t         uid;
    gid_t         gid;
    char         *chdir_path;
    char         *pts_path;
    mode_t        umask;
    lfp_rlimit_t *rlim;
    unsigned      rlim_size;
} lfp_spawnattr_t;

typedef enum {
        LFP_SPAWN_SETSIGMASK    = 1 <<  0,
#define LFP_SPAWN_SETSIGMASK    ( 1 <<  0 )
        LFP_SPAWN_SETSIGDEFAULT = 1 <<  1,
#define LFP_SPAWN_SETSIGDEFAULT ( 1 <<  1 )
        LFP_SPAWN_SETPGROUP     = 1 <<  2,
#define LFP_SPAWN_SETPGROUP     ( 1 <<  2 )
        LFP_SPAWN_RESETIDS      = 1 <<  3,
#define LFP_SPAWN_RESETIDS      ( 1 <<  3 )
        LFP_SPAWN_SETCWD        = 1 <<  6,
#define LFP_SPAWN_SETCWD        ( 1 <<  6 )
        LFP_SPAWN_SETSID        = 1 <<  7,
#define LFP_SPAWN_SETSID        ( 1 <<  7 )
        LFP_SPAWN_SETCTTY       = 1 <<  8,
#define LFP_SPAWN_SETCTTY       ( 1 <<  8 )
        LFP_SPAWN_USEVFORK      = 1 <<  9,
#define LFP_SPAWN_USEVFORK      ( 1 <<  9 )
        LFP_SPAWN_SETUMASK      = 1 << 10,
#define LFP_SPAWN_SETUMASK      ( 1 << 10 )
        LFP_SPAWN_SETRLIMIT     = 1 << 11,
#define LFP_SPAWN_SETRLIMIT     ( 1 << 11 )
} lfp_spawnattr_flags;

int lfp_spawnattr_init(lfp_spawnattr_t *attr);
int lfp_spawnattr_destroy(lfp_spawnattr_t *attr);

int lfp_spawnattr_getflags(lfp_spawnattr_t *attr, uint32_t *flags);
int lfp_spawnattr_setflags(lfp_spawnattr_t *attr, const uint32_t flags);

int lfp_spawnattr_getsigmask(lfp_spawnattr_t *attr, sigset_t *sigmask);
int lfp_spawnattr_setsigmask(lfp_spawnattr_t *attr, const sigset_t *sigmask);

int lfp_spawnattr_getsigdefault(lfp_spawnattr_t *attr, sigset_t *sigdefault);
int lfp_spawnattr_setsigdefault(lfp_spawnattr_t *attr, const sigset_t *sigdefault);

int lfp_spawnattr_getpgroup(lfp_spawnattr_t *attr, pid_t *pgroup);
int lfp_spawnattr_setpgroup(lfp_spawnattr_t *attr, const pid_t pgroup);

int lfp_spawnattr_setsid(lfp_spawnattr_t *attr);

int lfp_spawnattr_getctty(lfp_spawnattr_t *attr, char **path);
int lfp_spawnattr_setctty(lfp_spawnattr_t *attr, const char *path);

int lfp_spawnattr_getcwd(lfp_spawnattr_t *attr, char **path);
int lfp_spawnattr_setcwd(lfp_spawnattr_t *attr, const char *path);

int lfp_spawnattr_getumask(lfp_spawnattr_t *attr, mode_t *umask);
int lfp_spawnattr_setumask(lfp_spawnattr_t *attr, const mode_t umask);

int lfp_spawnattr_getrlimit(lfp_spawnattr_t *attr, lfp_rlimit_t **rlim, size_t *rlim_size);
int lfp_spawnattr_setrlimit(lfp_spawnattr_t *attr, const lfp_rlimit_t *rlim, size_t rlim_size);

int lfp_spawn(pid_t *restrict pid,
              const char *restrict path,
              char *const argv[restrict],
              char *const envp[restrict],
              const lfp_spawn_file_actions_t *restrict file_actions,
              const lfp_spawnattr_t *restrict attr);

int lfp_spawnp(pid_t *restrict pid,
               const char *restrict file,
               char *const argv[restrict],
               char *const envp[restrict],
               const lfp_spawn_file_actions_t *restrict file_actions,
               const lfp_spawnattr_t *restrict attr);

LFP_END_DECLS

#endif /* _LFP_SPAWN_H_ */
