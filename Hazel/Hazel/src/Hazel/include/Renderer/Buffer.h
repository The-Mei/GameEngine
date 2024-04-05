#pragma once

namespace Hazel
{
    enum class ShaderDataType
    {
        kNone = 0,
        kFloat,
        kFloat2,
        kFloat3,
        kFloat4,
        kMat3,
        kMat4,
        kInt,
        kInt2,
        kInt3,
        kInt4,
        kBool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::kFloat:
            return 4;
        case ShaderDataType::kFloat2:
            return 4 * 2;
        case ShaderDataType::kFloat3:
            return 4 * 3;
        case ShaderDataType::kFloat4:
            return 4 * 4;
        case ShaderDataType::kMat3:
            return 4 * 3 * 3;
        case ShaderDataType::kMat4:
            return 4 * 4 * 3;
        case ShaderDataType::kInt:
            return 4;
        case ShaderDataType::kInt2:
            return 4 * 2;
        case ShaderDataType::kInt3:
            return 4 * 3;
        case ShaderDataType::kInt4:
            return 4 * 4;
        case ShaderDataType::kBool:
            return 1;
        }
        HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
        return 0;
    }
    struct BufferElement
    {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement() {}

        BufferElement(ShaderDataType t, const std::string &na, bool normal = false)
            : name(na), type(t), size(ShaderDataTypeSize(t)), offset(0), normalized(normal)
        {
        }

        uint32_t getComponentCount() const
        {
            switch (type)
            {
            case ShaderDataType::kFloat:
                return 1;
            case ShaderDataType::kFloat2:
                return 2;
            case ShaderDataType::kFloat3:
                return 3;
            case ShaderDataType::kFloat4:
                return 4;
            case ShaderDataType::kMat3:
                return 3 * 3;
            case ShaderDataType::kMat4:
                return 4 * 4;
            case ShaderDataType::kInt:
                return 1;
            case ShaderDataType::kInt2:
                return 2;
            case ShaderDataType::kInt3:
                return 3;
            case ShaderDataType::kInt4:
                return 4;
            case ShaderDataType::kBool:
                return 1;
            }
            HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement> &elements)
            : mElements(elements)
        {
            calculateOffsetAndStride();
        }

        inline const std::vector<BufferElement> &getElements() const { return mElements; }
        inline uint32_t getStride() const { return mStride; }

        std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
        std::vector<BufferElement>::iterator end() { return mElements.end(); }

        std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

    private:
        void calculateOffsetAndStride()
        {
            uint32_t offset = 0;
            mStride = 0;
            for (auto &element : mElements)
            {
                element.offset = offset;
                offset += element.size;
                mStride += element.size;
            }
        }

    private:
        std::vector<BufferElement> mElements;
        uint32_t mStride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual void setLayout(const BufferLayout &layout) = 0;
        virtual const BufferLayout &getLayout() const = 0;

        static VertexBuffer *create(float *vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual uint32_t getCount() const = 0;

        static IndexBuffer *create(uint32_t *indices, uint32_t size);
    };
}