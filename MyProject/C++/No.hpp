#pragma once

class No {
private:
    int frequencia;

public:
    explicit No(int frequencia);
    virtual ~No() = default;

    int getFrequencia() const;
    void setFrequencia(int frequencia);
};