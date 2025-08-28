 class OrderPurchaser
 
   def initialize(order)
     @order = order
     @cart = order.cart
   end
   
   def process_purchase
    StripeWrapper::Charge.create(stripe_purchase_options)
   end
 
   def exception_params(e)
       }
     }
   end
     
 end
\ No newline at end of file