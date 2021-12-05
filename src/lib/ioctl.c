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

#include <lfp/ioctl.h>
#include <lfp/unistd.h>
#include <lfp/fcntl.h>
#include <lfp/stdlib.h>
#include <lfp/string.h>
#include <lfp/errno.h>

#include <string.h>
#include <termios.h>

DSO_PUBLIC int
lfp_tty_attach(const char *path)
{
    SYSCHECK(EINVAL, path == NULL);
    SYSCHECK(ENOENT, path[0] == '\0');

    int ttyfd;

    SYSGUARD(ttyfd = lfp_open(path, O_RDONLY | O_NOCTTY));
    if (lfp_tty_fattach(ttyfd) < 0) {
        int saved_errno = lfp_errno();
        close(ttyfd);
        SYSERR(saved_errno);
    } else {
        close(ttyfd);
    }

    return 0;
}

DSO_PUBLIC int
lfp_tty_fattach(int fd)
{
    SYSGUARD(ioctl(fd, TIOCSCTTY, 0));

    return 0;
}
