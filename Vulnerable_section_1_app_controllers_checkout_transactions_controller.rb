     def new
       if OrderPurchaser.new(order).purchase
         @transaction = order.transactions.last
         flash[:success] = 'Thank you for your order!'
         cart.inventory
         cart.save