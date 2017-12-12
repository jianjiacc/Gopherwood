
#ifndef _GOPHERWOOD_CORE_LOGFORMAT_H_
#define _GOPHERWOOD_CORE_LOGFORMAT_H_


#include <vector>
#include <stdio.h>
#include <stdint.h>

namespace Gopherwood {
    namespace Internal {

        class LogFormat {

        public:
            LogFormat();

            ~LogFormat();

            enum RecordType {

                acquireNewBlock = 0, // block type change 0 to 1

                inactiveBlock = 1, // block type change 1 to 2

                releaseBlock = 2,// block type change 1 to 0

                evictBlock = 3, // block move to OSS, so the type change 2 to a negative id in OSS,
                // and this block can be used by other apps, and the block will be changed 1 in other apps log

                remoteBlock = 4,// the block lists is in the OSS, the id is negative

                closeFile = 5,// the file have been closed and the FileStatus are collected and merged.


            };
            // Header is length (4 bytes), type (1 byte)
            const int kHeaderSize = 4 + 1;

        private:
            int length; // the length of the type;
            RecordType type;
            char data[1]; // the real data

        public:

            char *serializeBlockIDVector(const std::vector<int32_t> &blockIdVector);

            char *serializeLog(RecordType type, const std::vector<int32_t> &blockIdVector);

            char *serializeAcquireNewBlock(const std::vector<int32_t> &blockIdVector);

        };


    }
}

#endif //_GOPHERWOOD_CORE_LOGFORMAT_H_