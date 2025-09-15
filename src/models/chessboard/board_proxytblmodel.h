#ifndef CHESSBOARD_BOARD_PROXYTBLMODEL_H
#define CHESSBOARD_BOARD_PROXYTBLMODEL_H


namespace chessboard {

typedef QSortFilterProxyModel typedef33;
class ProxyTblModel : public typedef33 {
  public:
    inline explicit ProxyTblModel(QObject * parent = nullptr) : QSortFilterProxyModel(parent), m_white_on_bottom(true) {
            };

    QModelIndex mapFromSource(const QModelIndex & sourceIndex) const override;

    QModelIndex mapToSource(const QModelIndex & proxyIndex) const override;

    QModelIndex square_to_index(chess::Square square) const;

    inline void flip() {
                m_white_on_bottom = !m_white_on_bottom;
                invalidate();
            };


  private:
    bool m_white_on_bottom;

};

} // namespace chessboard
#endif
