//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//

#include "standardpch.h"
#include "runtimedetails.h"
#include "spmiutil.h"
#include "methodcallsummarizer.h"
#include "jithost.h"

JitHost* g_ourJitHost;

JitHost::JitHost(ICorJitHost* wrappedHost) : wrappedHost(wrappedHost), mcs(nullptr)
{
}

void JitHost::setMethodCallSummarizer(MethodCallSummarizer* methodCallSummarizer)
{
    this->mcs = methodCallSummarizer;
}

void* JitHost::allocateMemory(size_t size)
{
    return wrappedHost->allocateMemory(size);
}

void JitHost::freeMemory(void* block)
{
    return wrappedHost->freeMemory(block);
}

int JitHost::getIntConfigValue(const WCHAR* key, int defaultValue)
{
    mcs->AddCall("getIntConfigValue");
    return wrappedHost->getIntConfigValue(key, defaultValue);
}

const WCHAR* JitHost::getStringConfigValue(const WCHAR* key)
{
    mcs->AddCall("getStringConfigValue");
    return wrappedHost->getStringConfigValue(key);
}

void JitHost::freeStringConfigValue(const WCHAR* value)
{
    mcs->AddCall("freeStringConfigValue");
    wrappedHost->freeStringConfigValue(value);
}
