// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <mbedtls/sha256.h>
#include <openenclave/bits/enclavelibc.h>
#include <openenclave/bits/trace.h>
#include <openenclave/bits/sha.h>
#include <openenclave/types.h>

typedef struct _OE_SHA256ContextImpl
{
    mbedtls_sha256_context ctx;
} OE_SHA256ContextImpl;

OE_STATIC_ASSERT(sizeof(OE_SHA256ContextImpl) <= sizeof(OE_SHA256Context));

OE_Result OE_SHA256Init(OE_SHA256Context* context)
{
    OE_Result result = OE_UNEXPECTED;
    OE_SHA256ContextImpl* impl = (OE_SHA256ContextImpl*)context;

    if (!context)
        OE_THROW(OE_INVALID_PARAMETER);

    mbedtls_sha256_init(&impl->ctx);

    mbedtls_sha256_starts(&impl->ctx, 0);

    OE_THROW(OE_OK);

OE_CATCH:
    return result;
}

OE_Result OE_SHA256Update(
    OE_SHA256Context* context,
    const void* data,
    size_t size)
{
    OE_Result result = OE_INVALID_PARAMETER;
    OE_SHA256ContextImpl* impl = (OE_SHA256ContextImpl*)context;

    if (!context || !data)
        OE_THROW(OE_INVALID_PARAMETER);

    mbedtls_sha256_update(&impl->ctx, data, size);

    OE_THROW(OE_OK);

OE_CATCH:
    return result;
}

OE_Result OE_SHA256Final(OE_SHA256Context* context, OE_SHA256* sha256)
{
    OE_Result result = OE_INVALID_PARAMETER;
    OE_SHA256ContextImpl* impl = (OE_SHA256ContextImpl*)context;

    if (!context || !sha256)
        OE_THROW(OE_INVALID_PARAMETER);

    mbedtls_sha256_finish(&impl->ctx, sha256->buf);

    OE_THROW(OE_OK);

OE_CATCH:
    return result;
}
