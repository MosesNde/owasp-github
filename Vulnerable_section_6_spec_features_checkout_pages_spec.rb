     expect(page).to have_content(@product.options.last.model)
     check('order_terms_validator_accept_terms')
     click_button('Place Order')
    expect(page).to have_content('Transaction ID')
     expect(page).to have_content('0 Items')
   end
 
     expect(page).to have_content(@product.options.last.model)
     check('order_terms_validator_accept_terms')
     click_button('Place Order')
    expect(page).to have_content('Transaction ID')
     expect(page).to have_content('0 Items')
     test_sign_out(true)
   end