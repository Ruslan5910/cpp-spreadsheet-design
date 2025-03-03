#pragma once

#include "common.h"
#include "formula.h"

#include <unordered_set>

class Impl {
public:
    virtual ~Impl();
    virtual std::string GetText() = 0;
    virtual CellInterface::Value GetValue() = 0;
};

class EmptyImpl : public Impl {
public:
    std::string GetText() override;
    CellInterface::Value GetValue();
};

class TextImpl : public Impl {
public:
    TextImpl(std::string text);
    std::string GetText() override;
    CellInterface::Value GetValue();
private:
    std::string text_;
};

class FormulaImpl : public Impl {
public:
    FormulaImpl(std::string text);
    std::string GetText() override;
    CellInterface::Value GetValue();
private:
    std::unique_ptr<FormulaInterface> formula_;
};


class Cell : public CellInterface {
public:
    Cell(Sheet& sheet);
    ~Cell();
    void Set(std::string text);
    void Clear();
    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

private:
    std::unique_ptr<Impl> impl_;
    Sheet& sheet_reference;
    std::unordered_set<Cell*> dependent_cell;
    std::unordered_set<Cell*> which_depends_on;
};
