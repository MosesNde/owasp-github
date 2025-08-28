       allow(order).to receive(:stripe_purchase?) { true }
       OrderPurchaser.new(order).purchase
       expect(order.transactions.count).to eq 1
       expect(order.transactions.last.action).to eq 'stripe purchase'
       expect(order.transactions.last.amount).to eq 999
       expect(order.transactions.last.success).to be true