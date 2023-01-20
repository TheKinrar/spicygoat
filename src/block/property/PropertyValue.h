//
// Created by thekinrar on 19/01/23.
//

#pragma once

class PropertyValue {
    const int type;

   protected:
    explicit PropertyValue(int type) : type(type) {}

   public:
    [[nodiscard]]
    int getType() const {
        return type;
    }

    [[nodiscard]]
    virtual bool equals(const PropertyValue& other) const = 0;

    [[nodiscard]]
    virtual std::string toString() const = 0;

    template <class T>
    static std::vector<std::shared_ptr<T>> wrap(const std::vector<T>& src) {
        std::vector<std::shared_ptr<T>> dst;
        for(const auto &item : src)
            dst.push_back(std::make_unique<T>(item));
        return dst;
    }
};
