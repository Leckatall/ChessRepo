//
// Created by Lecka on 22/09/2025.
//

#include "test_proxy_board_model.h"

void Test::TestProxyBoardModel::initTestCase() {
    m_model = new chessboard::TblModel();
    m_proxyModel = new chessboard::ProxyTblModel();
    m_proxyModel->setSourceModel(m_model);
    test_white_on_bottom_squares[{0, 0}] = new QModelIndex(m_model->index(7, 0));
    test_white_on_bottom_squares[{7, 7}] = new QModelIndex(m_model->index(0, 7));
    test_white_on_bottom_squares[{3, 4}] = new QModelIndex(m_model->index(3, 4));
    test_black_on_bottom_squares[{0, 0}] = new QModelIndex(m_model->index(0, 7));
    test_black_on_bottom_squares[{7, 7}] = new QModelIndex(m_model->index(7, 0));
    test_black_on_bottom_squares[{3, 4}] = m_model->index(4, 3);
}

void Test::TestProxyBoardModel::testSquareToIndex() {
    const Domain::Types::Chess::Square a1 = {0, 0};
    const Domain::Types::Chess::Square h8 = {7, 7};
    const Domain::Types::Chess::Square e4 = {3, 4};
    QCOMPARE(m_model->squareToIndex(a1), QModelIndex(m_model->index(7, 0)));
    QCOMPARE(m_model->squareToIndex(h8), QModelIndex(m_model->index(0, 7)));
    QCOMPARE(m_model->squareToIndex(e4), QModelIndex(m_model->index(3, 4)));
    for (auto [sq, idx]: test_white_on_bottom_squares) {
        QCOMPARE(m_proxyModel->mapToSource(idx), m_model->squareToIndex(sq));
    }
    
}

void Test::TestProxyBoardModel::testIndexToSquare() {
    
}
