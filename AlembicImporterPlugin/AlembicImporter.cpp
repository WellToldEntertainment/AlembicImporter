﻿#include "pch.h"
#include "AlembicImporter.h"
#include "aiLogger.h"
#include "aiContext.h"
#include "aiObject.h"
#include "Schema/aiSchema.h"
#include "Schema/aiXForm.h"
#include "Schema/aiPolyMesh.h"
#include "Schema/aiCamera.h"
#include "Schema/aiPoints.h"

#ifdef aiWindows
    #include <windows.h>

#   define aiBreak() DebugBreak()
#else // aiWindows
#   define aiBreak() __builtin_trap()
#endif // aiWindows


aiCLinkage aiExport void aiEnableFileLog(bool on, const char *path)
{
    aiLogger::Enable(on, path);
}

aiCLinkage aiExport void aiCleanup()
{
#ifdef aiWithTBB
#else
    aiThreadPool::releaseInstance();
#endif
}

aiCLinkage aiExport aiContext* aiCreateContext(int uid)
{
    auto ctx = aiContext::create(uid);
    return ctx;
}

aiCLinkage aiExport void aiDestroyContext(aiContext* ctx)
{
    aiContext::destroy(ctx);
}


aiCLinkage aiExport bool aiLoad(aiContext* ctx, const char *path)
{
    return ctx->load(path);
}

aiCLinkage aiExport void aiSetConfig(aiContext* ctx, const aiConfig* conf)
{
    ctx->setConfig(*conf);
}

aiCLinkage aiExport float aiGetStartTime(aiContext* ctx)
{
    return ctx->getStartTime();
}

aiCLinkage aiExport float aiGetEndTime(aiContext* ctx)
{
    return ctx->getEndTime();
}

aiCLinkage aiExport aiObject* aiGetTopObject(aiContext* ctx)
{
    return ctx->getTopObject();
}

aiCLinkage aiExport void aiDestroyObject(aiContext* ctx, aiObject* obj)
{
    ctx->destroyObject(obj);
}

aiCLinkage aiExport void aiUpdateSamples(aiContext* ctx, float time)
{
    ctx->updateSamples(time);
}

aiCLinkage aiExport void aiEnumerateChild(aiObject *obj, aiNodeEnumerator e, void *userData)
{
    size_t n = obj->getNumChildren();

    for (size_t i = 0; i < n; ++i)
    {
        try
        {
            aiObject *child = obj->getChild(i);
            e(child, userData);
        }
        catch (Alembic::Util::Exception e)
        {
            DebugLog("aiEnumerateChlid: %s", e.what());
        }
    }
}

aiCLinkage aiExport const char* aiGetNameS(aiObject* obj)
{
    return obj->getName();
}

aiCLinkage aiExport const char* aiGetFullNameS(aiObject* obj)
{
    return obj->getFullName();
}


aiCLinkage aiExport void aiSchemaSetSampleCallback(aiSchemaBase* schema, aiSampleCallback cb, void* arg)
{
    schema->setSampleCallback(cb, arg);
}

aiCLinkage aiExport void aiSchemaSetConfigCallback(aiSchemaBase* schema, aiConfigCallback cb, void* arg)
{
    schema->setConfigCallback(cb, arg);
}

aiCLinkage aiExport const aiSampleBase* aiSchemaUpdateSample(aiSchemaBase* schema, float time)
{
    return schema->updateSample(time);
}

aiCLinkage aiExport const aiSampleBase* aiSchemaGetSample(aiSchemaBase* schema, float time)
{
    return schema->findSample(time);
}


aiCLinkage aiExport bool aiHasXForm(aiObject* obj)
{
    return obj->hasXForm();
}

aiCLinkage aiExport aiXForm* aiGetXForm(aiObject* obj)
{
    return &(obj->getXForm());
}

aiCLinkage aiExport void aiXFormGetData(aiXFormSample* sample, aiXFormData *outData)
{
    sample->getData(*outData);
}


aiCLinkage aiExport bool aiHasPolyMesh(aiObject* obj)
{
    return obj->hasPolyMesh();
}

aiCLinkage aiExport aiPolyMesh* aiGetPolyMesh(aiObject* obj)
{
    return &(obj->getPolyMesh());
}

aiCLinkage aiExport void aiPolyMeshGetSummary(aiPolyMesh* schema, aiMeshSummary* summary)
{
    schema->getSummary(*summary);
}

aiCLinkage aiExport void aiPolyMeshGetSampleSummary(aiPolyMeshSample* sample, aiMeshSampleSummary* summary, bool forceRefresh)
{
    sample->getSummary(forceRefresh, *summary);
}

aiCLinkage aiExport int aiPolyMeshGetVertexBufferLength(aiPolyMeshSample* sample, int splitIndex)
{
    return sample->getVertexBufferLength(splitIndex);
}

aiCLinkage aiExport void aiPolyMeshFillVertexBuffer(aiPolyMeshSample* sample, int splitIndex, aiMeshSampleData* data)
{
    sample->fillVertexBuffer(splitIndex, *data);
}

aiCLinkage aiExport int aiPolyMeshPrepareSubmeshes(aiPolyMeshSample* sample, const aiFacesets* facesets)
{
    return sample->prepareSubmeshes(*facesets);
}

aiCLinkage aiExport int aiPolyMeshGetSplitSubmeshCount(aiPolyMeshSample* sample, int splitIndex)
{
    return sample->getSplitSubmeshCount(splitIndex);
}

aiCLinkage aiExport bool aiPolyMeshGetNextSubmesh(aiPolyMeshSample* sample, aiSubmeshSummary* summary)
{
    return sample->getNextSubmesh(*summary);
}

aiCLinkage aiExport void aiPolyMeshFillSubmeshIndices(aiPolyMeshSample* sample, const aiSubmeshSummary* summary, aiSubmeshData* data)
{
    sample->fillSubmeshIndices(*summary, *data);
}


aiCLinkage aiExport bool aiHasCamera(aiObject* obj)
{
    return obj->hasCamera();
}

aiCLinkage aiExport aiCamera* aiGetCamera(aiObject* obj)
{
    return &(obj->getCamera());
}

aiCLinkage aiExport void aiCameraGetData(aiCameraSample* sample, aiCameraData *outData)
{
    sample->getData(*outData);
}


aiCLinkage aiExport bool aiHasPoints(aiObject* obj)
{
    return obj->hasPoints();
}

aiCLinkage aiExport aiPoints* aiGetPoints(aiObject* obj)
{
    return &(obj->getPoints());
}

aiCLinkage aiExport void aiPointsGetData(aiPointsSample* sample, aiPointsSampleData *outData)
{
    sample->fillData(*outData);
}