#ifndef GPTJ_H
#define GPTJ_H

#include <string>
#include <functional>
#include <vector>
#include "llmodel.h"

//Need this for windows.
#ifdef _WIN32
    #define NOMINMAX
    #include <io.h>
    #include <windows.h> 
#else
    #include <unistd.h>
#endif

class GPTJPrivate;
class GPTJ : public LLModel {
public:
    GPTJ();
    ~GPTJ();

    bool loadModel(const std::string &modelPath) override;
    bool loadModel(const std::string &modelPath, std::istream &fin) override;
    bool isModelLoaded() const override;
    void prompt(const std::string &prompt,
        std::function<bool(int32_t)> promptCallback,
        std::function<bool(int32_t, const std::string&)> responseCallback,
        std::function<bool(bool)> recalculateCallback,
        PromptContext &ctx) override;
    void setThreadCount(int32_t n_threads) override;
    int32_t threadCount() override;

protected:
    void recalculateContext(PromptContext &promptCtx,
        std::function<bool(bool)> recalculate) override;

private:
    GPTJPrivate *d_ptr;
};

#endif // GPTJ_H
