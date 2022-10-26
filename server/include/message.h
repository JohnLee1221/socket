#ifndef __MESSAGE__
#define __MESSAGE__
#include <stdint.h>


typedef struct Os_lxCanMessage_Tag
{
    uint32_t                messageId;                   /**< \brief ID, Identifier */
    uint32_t                messageIdLength;             /**< \brief XTD, Message Id length (Standard / Extended) */
    uint32_t                dataLengthCode;              /**< \brief DLC, Data Length Code */
    uint64_t                data;
}Os_lxCanMessage;

#endif