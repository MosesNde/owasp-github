 class OrderPurchaser
 
  # require 'active_merchant/billing/rails'

   def initialize(order)
     @order = order
     @cart = order.cart
   end
   
   def process_purchase
    if @order.stripe_purchase?
      StripeWrapper::Charge.create(stripe_purchase_options)
    else
      # EXPRESS_GATEWAY.purchase(@total, express_purchase_options)
    end
   end
 
   def exception_params(e)
       }
     }
   end

  def express_purchase_options
    {
      ip:       @order.ip_address,
      token:    @order.express_token,
      payer_id: @order.express_payer_id
    }
  end
     
 end
\ No newline at end of file