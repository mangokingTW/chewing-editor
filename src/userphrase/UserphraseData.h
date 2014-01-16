#pragma once

#include <string>
#include <vector>

struct Userphrase final {
    std::string phrase_;
    std::string bopomofo_;
};

class UserphraseData {
public:
    UserphraseData() = default;
    UserphraseData(const UserphraseData&) = delete;
    UserphraseData& operator=(const UserphraseData&) = delete;
    virtual ~UserphraseData() = default;

    size_t size() const;
    const Userphrase& get(size_t index);
    void add(std::string &&phrase_, std::string &&bopomofo_);
    bool remove(const std::vector<size_t> &index);

    void swap(std::vector<Userphrase> &userphrase);

    void refresh();
    void save();

protected:
    virtual void refresh_impl() = 0;
    virtual void save_impl() = 0;
    virtual bool remove_impl(const std::vector<size_t> &index) = 0;

    std::vector<Userphrase> userphrase_;
    std::vector<Userphrase> undo_;
};
