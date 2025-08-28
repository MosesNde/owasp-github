     def new
       if OrderPurchaser.new(order).purchase
         @transaction = order.transactions.last

        # for display only, not persisted
        @transaction.authorization.gsub!('ch_', '')

         flash[:success] = 'Thank you for your order!'
         cart.inventory
         cart.save